#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/Color.hpp>

#define ROWS 5
#define COLS 6
#define EMPTY 0
#define RED 1
#define BLUE 2
#define GREEN 3
#define YELLOW 4
#define PURPLE 5

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    void initEggGrid();
    void renderEggGrid();
    void spawnNextEgg();
    void updateScore();
    void clearEggGrid();
    void ensureMatchablePattern();
    void dropEggGrid();
    void addNewTopRow();
private:
    uint8_t eggGrid[ROWS][COLS];
    touchgfx::Image eggImages[ROWS][COLS];
    int score;
    Unicode::UnicodeChar scoreBuffer[10];
    int shotCount;           // Đếm số lần bắn
	static const int SHOTS_BEFORE_DROP = 5; // Sau 5 lần bắn thì hạ xuống
	void onEggShot();        // Gọi mỗi khi bắn trứng
	bool checkGameOver();
};

#endif // SCREEN2VIEW_HPP
