#include <gui/gameover_screen/GameOverView.hpp>

GameOverView::GameOverView()
{

}

void GameOverView::setupScreen()
{
    GameOverViewBase::setupScreen();
    finalScore.setWildcard(scoreBuffer);  // ← Cố định
    scoreBuffer[0] = 0;
}

void GameOverView::tearDownScreen()
{
    GameOverViewBase::tearDownScreen();
}
void GameOverView::showScore(int s)
{
	Unicode::snprintf(scoreBuffer,
	                      sizeof(scoreBuffer) / sizeof(Unicode::UnicodeChar),
	                      "%d",
	                      s);
    finalScore.invalidate();
}
