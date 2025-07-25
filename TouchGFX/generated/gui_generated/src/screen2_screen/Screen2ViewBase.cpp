/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase()
{
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    canon.setBitmap(touchgfx::Bitmap(BITMAP_CANNON_ID));
    canon.setPosition(90, 279, 60, 40);
    canon.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(canon);

    nextEgg.setBitmap(touchgfx::Bitmap(BITMAP_EGG_RED_ID));
    nextEgg.setPosition(102, 239, 36, 36);
    nextEgg.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(nextEgg);

    scoreText.setXY(74, 0);
    scoreText.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    scoreText.setLinespacing(0);
    Unicode::snprintf(scoreTextBuffer, SCORETEXT_SIZE, "%s", touchgfx::TypedText(T_SCORETEXTVALUE).getText());
    scoreText.setWildcard(scoreTextBuffer);
    scoreText.resizeToCurrentText();
    scoreText.setTypedText(touchgfx::TypedText(T_SCORETEXT));
    add(scoreText);

    container1.setPosition(0, 239, 240, 80);
    add(container1);

    container2.setPosition(0, 24, 240, 215);
    add(container2);

    container3.setPosition(0, 0, 240, 24);
    add(container3);
}

Screen2ViewBase::~Screen2ViewBase()
{

}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::handleKeyEvent(uint8_t key)
{
    if(0 == key)
    {
        //Interaction1
        //When hardware button 0 clicked change screen to GameOver
        //Go to GameOver with no screen transition
        application().gotoGameOverScreenNoTransition();
    
    }
}
