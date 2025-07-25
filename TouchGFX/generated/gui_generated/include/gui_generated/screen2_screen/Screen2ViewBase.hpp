/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN2VIEWBASE_HPP
#define SCREEN2VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>

class Screen2ViewBase : public touchgfx::View<Screen2Presenter>
{
public:
    Screen2ViewBase();
    virtual ~Screen2ViewBase();
    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::ScalableImage canon;
    touchgfx::ScalableImage nextEgg;
    touchgfx::TextAreaWithOneWildcard scoreText;
    touchgfx::Container container1;
    touchgfx::Container container2;
    touchgfx::Container container3;

    /*
     * Wildcard Buffers
     */
    static const uint16_t SCORETEXT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar scoreTextBuffer[SCORETEXT_SIZE];

private:

};

#endif // SCREEN2VIEWBASE_HPP
