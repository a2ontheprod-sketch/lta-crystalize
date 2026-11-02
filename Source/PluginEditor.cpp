#include "PluginEditor.h"

namespace {
const juce::Colour yellow { 0xffe7cf18 }, brightYellow { 0xffffe52b };
const juce::Colour green { 0xff153d12 }, green2 { 0xff347b1c };
const juce::Colour blue { 0xff35bce8 }, paleBlue { 0xff9beaff };

void crystal (juce::Graphics& g, float x, float y, float size, float angle)
{
    juce::Path p; p.addTriangle (0, -size, size*.62f, size*.48f, -size*.62f, size*.48f);
    p.applyTransform (juce::AffineTransform::rotation(angle).translated(x,y));
    g.setColour(blue); g.fillPath(p);
    g.setColour(paleBlue.withAlpha(.65f));
    juce::Path facet; facet.startNewSubPath(x,y-size); facet.lineTo(x,y+size*.48f);
    facet.lineTo(x+size*.62f,y+size*.48f); facet.closeSubPath(); g.fillPath(facet);
    g.setColour(juce::Colour(0xff147a9a)); g.strokePath(p, juce::PathStrokeType(1.2f));
}
void bag (juce::Graphics& g, juce::Rectangle<float> r, float amount)
{
    juce::Path p; p.startNewSubPath(r.getX()+7,r.getY()+5); p.lineTo(r.getRight()-7,r.getY()+5);
    p.lineTo(r.getRight()-13,r.getBottom()-5);
    p.quadraticTo(r.getCentreX(),r.getBottom()+2,r.getX()+13,r.getBottom()-5); p.closeSubPath();
    g.setColour(juce::Colour(0x22ffffff)); g.fillPath(p);
    g.setColour(green); g.strokePath(p,juce::PathStrokeType(3));
    g.setColour(green2); g.drawLine(r.getX()+7,r.getY()+12,r.getRight()-7,r.getY()+12,4);
    int n=(int)std::round(juce::jlimit(0.0f,1.0f,amount)*13);
    for(int i=0;i<n;++i) crystal(g,r.getX()+24+(i*31)%95,r.getBottom()-12-(i*17)%42,8+(i%4)*1.5f,(i%3)*.3f);
}
}

LTACrystalizeAudioProcessorEditor::LTACrystalizeAudioProcessorEditor(LTACrystalizeAudioProcessor& p)
: AudioProcessorEditor(&p), processor(p)
{
    setSize(760,430);
    button.setColour(juce::TextButton::buttonColourId,green);
    button.setColour(juce::TextButton::buttonOnColourId,green2);
    button.setColour(juce::TextButton::textColourOffId,brightYellow);
    button.setColour(juce::TextButton::textColourOnId,brightYellow);
    button.setClickingTogglesState(true);
    button.setToggleState(processor.isCrystalized(),juce::dontSendNotification);
    button.onClick=[this]{ processor.setCrystalized(button.getToggleState()); startAnimation(); repaint(); };
    addAndMakeVisible(button); startTimerHz(30);
}
void LTACrystalizeAudioProcessorEditor::resized(){ button.setBounds(getWidth()/2-188,278,376,88); }
void LTACrystalizeAudioProcessorEditor::startAnimation()
{
    progress=0; animating=true; startMs=juce::Time::getMillisecondCounterHiRes();
}
void LTACrystalizeAudioProcessorEditor::timerCallback()
{
    if(animating){ progress=juce::jlimit(0.0f,1.0f,(float)((juce::Time::getMillisecondCounterHiRes()-startMs)/1150.0));
        if(progress>=1) animating=false; repaint(); }
}
void LTACrystalizeAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(yellow);
    g.setColour(brightYellow.withAlpha(.35f));
    juce::Path deco; deco.startNewSubPath(0,80); deco.lineTo(135,80); deco.lineTo(0,185); deco.closeSubPath(); g.fillPath(deco);
    g.setColour(green); g.fillRect(0,0,getWidth(),72);
    g.setColour(brightYellow); g.fillRect(0,70,getWidth(),3);
    g.setFont(juce::Font("Consolas",27,juce::Font::bold)); g.drawText("LTA",22,17,66,42,juce::Justification::centredLeft);
    g.drawText("LTA Crystalize",103,17,360,42,juce::Justification::centredLeft);
    g.setFont(juce::Font("Consolas",18,juce::Font::bold)); g.drawText("V1.0.1",getWidth()-112,20,78,34,juce::Justification::centredRight);

    float pr=animating?progress:1.0f, alpha=1.0f-pr*.72f;
    g.setColour(green.withAlpha(alpha));
    for(int i=0;i<23;++i){ float x=112+i*(235.0f/22), env=std::sin(i/22.0f*juce::MathConstants<float>::pi);
        float h=8+env*(.28f+.72f*std::abs(std::sin(i*1.71f)))*82;
        g.fillRoundedRectangle(x-3,184-h*.5f,6,h,3); }
    g.setColour(green2); juce::Path a; a.startNewSubPath(378,184); a.lineTo(449,184); a.lineTo(432,168);
    a.startNewSubPath(449,184); a.lineTo(432,200);
    g.strokePath(a,juce::PathStrokeType(7,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    bag(g,{490,112,154,151},animating?progress:(processor.isCrystalized()?1.0f:.72f));
    if(animating && progress<.9f) for(int i=0;i<5;++i){
        float t=juce::jlimit(0.0f,1.0f,progress*1.25f);
        crystal(g,juce::jmap(t,355.0f+i*12,540.0f+i*12),145+std::sin(progress*8+i)*24+t*65,
                9+(i%3)*3,progress*5+i); }
    g.setColour(green.withAlpha(.85f)); g.setFont(juce::Font("Consolas",13,juce::Font::bold));
    g.drawText("LTA // AUDIO CRYSTALLISATION UNIT",22,getHeight()-28,390,18,juce::Justification::centredLeft);
    g.drawText(processor.isCrystalized()?"ACTIVE":"STANDBY",getWidth()-110,getHeight()-28,88,18,juce::Justification::centredRight);
    g.setColour(green); g.drawRect(1,1,getWidth()-2,getHeight()-2,2);
}
