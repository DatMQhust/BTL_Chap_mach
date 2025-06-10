#include <gui/screen2_screen/Screen2View.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/Unicode.hpp>
#include "main.h"

Screen2View::Screen2View() : score(0),shotCount(0)
{
    // Khởi tạo mảng eggGrid
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            eggGrid[i][j] = EMPTY;
        }
    }
}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    // Khởi tạo tất cả eggImages và thêm vào box2 (khu vực game chính)
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            eggImages[row][col].setVisible(false);
            container2.add(eggImages[row][col]);
        }
    }
    shotCount = 0;
    // Khởi tạo game
    initEggGrid();
    renderEggGrid();
    spawnNextEgg();
    updateScore();


}

void Screen2View::tearDownScreen()
{
    clearEggGrid();
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::initEggGrid()
{
    // Xóa toàn bộ grid trước
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            eggGrid[row][col] = EMPTY;
        }
    }

    uint32_t baseTick = HAL_GetTick();

    for(int row = 0; row < 3; row++) // 3 hàng đầu
    {
        int maxCols = COLS;

        // Giảm số lượng trứng theo từng hàng
        switch(row)
        {
            case 0: maxCols = COLS; break;
            case 1: maxCols = COLS; break;
            case 2: maxCols = COLS; break;
        }

        // Căn giữa các trứng trong hàng
        int startCol = (COLS - maxCols) / 2;

        for(int col = 0; col < maxCols; col++)
        {
            int actualCol = startCol + col;
            if(actualCol >= 0 && actualCol < COLS)
            {
                // Tạo màu ngẫu nhiên nhưng đảm bảo có thể match được
                uint32_t seed = baseTick + row * 13 + col * 7;
                eggGrid[row][actualCol] = (seed % 5) + 1;
            }
        }
    }

    // Tạo một số pattern có thể match được dễ dàng
    ensureMatchablePattern();
}

void Screen2View::ensureMatchablePattern()
{
    // Tạo một vài nhóm 2 quả cùng màu để dễ match
    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < COLS - 1; col++)
        {
            if(eggGrid[row][col] != EMPTY && eggGrid[row][col + 1] != EMPTY)
            {
                // 30% cơ hội tạo cặp cùng màu
                uint32_t chance = (HAL_GetTick() + row * col) % 100;
                if(chance < 30)
                {
                    eggGrid[row][col + 1] = eggGrid[row][col];
                }
            }
        }
    }
}

void Screen2View::renderEggGrid()
{
    // Lấy vị trí của box2 để làm offset
    int baseX = container2.getX();
    int baseY = container2.getY();

    // Kích thước trứng và khoảng cách
    const int EGG_WIDTH = 32;
    const int EGG_HEIGHT = 32;
    const int EGG_SPACING_X = 36; // Khoảng cách ngang
    const int EGG_SPACING_Y = 31; // Khoảng cách dọc (nhỏ hơn để tạo hiệu ứng chồng lên)
    const int HEX_OFFSET = 18;    // Offset cho hàng lẻ tạo pattern hexagonal

    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            if(eggGrid[row][col] != EMPTY)
            {
                // Chọn bitmap theo màu
                switch(eggGrid[row][col])
                {
                    case RED:    eggImages[row][col].setBitmap(BITMAP_EGG_RED_ID); break;
                    case BLUE:   eggImages[row][col].setBitmap(BITMAP_EGG_BLUE_ID); break;
                    case GREEN:  eggImages[row][col].setBitmap(BITMAP_EGG_GREEN_ID); break;
                    case YELLOW: eggImages[row][col].setBitmap(BITMAP_EGG_YELLOW_ID); break;
                    case PURPLE: eggImages[row][col].setBitmap(BITMAP_EGG_PURPLE_ID); break;
                }

                // Tính toán vị trí hexagonal pattern
                int xOffset = (row % 2 == 1) ? HEX_OFFSET : 0; // Hàng lẻ lệch phải
                int x = baseX + col * EGG_SPACING_X + xOffset;
                int y = baseY + row * EGG_SPACING_Y;

                eggImages[row][col].setXY(x, y);
                eggImages[row][col].setWidthHeight(EGG_WIDTH, EGG_HEIGHT);
                eggImages[row][col].setVisible(true);
            }
            else
            {
                eggImages[row][col].setVisible(false);
            }
        }
    }

    // Invalidate toàn bộ view
    container2.invalidate();
}
// Function được gọi mỗi khi người chơi bắn trứng
void Screen2View::onEggShot()
{
    shotCount++;

    // Sau mỗi SHOTS_BEFORE_DROP lần bắn, hạ lưới xuống
    if(shotCount >= SHOTS_BEFORE_DROP)
    {
        dropEggGrid();
        shotCount = 0; // Reset counter

//        // Kiểm tra game over
//        if(checkGameOver())
//        {
//            // Chuyển sang Screen 3 (Game Over)
//            application().gotoScreen3ScreenNoTransition();
//            return;
//        }
    }

    // Spawn trứng mới cho lần bắn tiếp theo
    spawnNextEgg();
}

void Screen2View::dropEggGrid()
{
    // Di chuyển tất cả trứng xuống 1 hàng
    for(int row = ROWS - 1; row > 0; row--)
    {
        for(int col = 0; col < COLS; col++)
        {
            eggGrid[row][col] = eggGrid[row - 1][col];
        }
    }

    // Thêm hàng mới ở trên (có thể random hoặc theo pattern)
    addNewTopRow();

    // Render lại
    renderEggGrid();
}

void Screen2View::addNewTopRow()
{
    // Thêm hàng mới ở trên với pattern logic
    uint32_t tick = HAL_GetTick();

    // 70% cơ hội có trứng ở hàng mới
    for(int col = 0; col < COLS; col++)
    {
        uint32_t seed = tick + col * 23;
        if((seed % 100) < 70)
        {
            eggGrid[0][col] = (seed % 5) + 1; // Random màu
        }
        else
        {
            eggGrid[0][col] = EMPTY;
        }
    }
}

bool Screen2View::checkGameOver()
{
    // Kiểm tra xem có trứng nào ở hàng cuối không
    for(int col = 0; col < COLS; col++)
    {
        if(eggGrid[ROWS - 1][col] != EMPTY)
        {
            return true; // Game Over!
        }
    }

    // Hoặc kiểm tra xem có trứng nào quá gần đường bắn không
    for(int col = 0; col < COLS; col++)
    {
        if(eggGrid[ROWS - 2][col] != EMPTY) // Hàng áp cuối
        {
            return true; // Sắp Game Over
        }
    }

    return false;
}


void Screen2View::spawnNextEgg()
{
    uint32_t tick = HAL_GetTick();
    uint8_t color = (tick % 5) + 1;

    switch(color)
    {
        case RED:    nextEgg.setBitmap(BITMAP_EGG_RED_ID); break;
        case BLUE:   nextEgg.setBitmap(BITMAP_EGG_BLUE_ID); break;
        case GREEN:  nextEgg.setBitmap(BITMAP_EGG_GREEN_ID); break;
        case YELLOW: nextEgg.setBitmap(BITMAP_EGG_YELLOW_ID); break;
        case PURPLE: nextEgg.setBitmap(BITMAP_EGG_PURPLE_ID); break;
    }

    nextEgg.invalidate();
}

void Screen2View::updateScore()
{
    Unicode::snprintf(scoreTextBuffer, 10, "%d", score);
    scoreText.setWildcard(scoreTextBuffer);
    scoreText.invalidate();
}

void Screen2View::clearEggGrid()
{
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            eggImages[row][col].setVisible(false);
            eggGrid[row][col] = EMPTY;
        }
    }
}
