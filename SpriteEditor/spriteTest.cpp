// /**
//  * @file spriteTest.cpp
//  * @brief Unit tests for the Sprite class.
//  *
//  * This file contains tests for Sprite frame management and
//  * animation data.
//  *
//  * Team: Green Goombas
//  * @authors Charles Adair, Armando Carrillo, Parker Hollingsed, Brady Nelson, Lindsey Reese, Kent Wilkison
//  * @date 3-26-2026
//  */

// #include <QtTest/QtTest>
// #include "sprite.h"

// class SpriteTest : public QObject
// {
//     Q_OBJECT

// private slots:
//     // ---------- constructor ----------
//     void Constructor_DefaultSprite_FrameCountIsOne();
//     void Constructor_DefaultSprite_CurrentFrameIndexIsZero();
//     void Constructor_DefaultSprite_FPSIsDefault();
//     void Constructor_DefaultSprite_FrameHasDefaultResolution();   // if width/height are public

//     // ---------- addFrame ----------
//     void AddFrame_ValidFrame_FrameCountIncreases();

//     // ---------- removeFrame ----------
//     void RemoveFrame_ValidIndex_FrameCountDecreases();
//     void RemoveFrame_OnlyFrame_FrameCountStaysOne();
//     void RemoveFrame_OnlyFrame_CurrentFrameIndexStaysZero();
//     void RemoveFrame_NegativeIndex_FrameCountDoesNotChange();
//     void RemoveFrame_IndexTooLarge_FrameCountDoesNotChange();

//     // ---------- duplicateFrame ----------
//     void DuplicateFrame_ValidIndex_FrameCountIncreases();
//     void DuplicateFrame_NegativeIndex_FrameCountDoesNotChange();
//     void DuplicateFrame_IndexTooLarge_FrameCountDoesNotChange();

//     // ---------- moveFrame ----------
//     void MoveFrame_SameIndex_FrameCountDoesNotChange();
//     void MoveFrame_NegativeFromIndex_FrameCountDoesNotChange();
//     void MoveFrame_FromIndexTooLarge_FrameCountDoesNotChange();
//     void MoveFrame_NegativeToIndex_FrameCountDoesNotChange();
//     void MoveFrame_ToIndexTooLarge_FrameCountDoesNotChange();

//     // ---------- getCurrentFrame ----------
//     void GetCurrentFrame_DefaultSprite_ReturnsFrame();
//     void GetCurrentFrame_AfterRemovingOnlyFrame_ReturnsFrame();

//     // ---------- getCurrentFrameIndex ----------
//     void GetCurrentFrameIndex_DefaultSprite_ReturnsZero();
//     void GetCurrentFrameIndex_AfterAddFrame_RemainsZero();
//     void GetCurrentFrameIndex_AfterDuplicateFrame_RemainsSame();
//     void GetCurrentFrameIndex_AfterRemovingOnlyFrame_IsZero();

//     // ---------- getFrame ----------
//     void GetFrame_ValidIndex_ReturnsFrame();
//     void GetFrame_MultipleFrames_ValidIndex_ReturnsFrame();
//     void GetFrame_NegativeIndex_ThrowsException();
//     void GetFrame_IndexTooLarge_ThrowsException();

//     // ---------- getFPS ----------
//     void GetFPS_DefaultSprite_ReturnsDefaultFPS();
//     void GetFPS_AfterSetFPS_ReturnsUpdatedValue();
//     void GetFPS_AfterSetZeroFPS_ReturnsPreviousValue();
//     void GetFPS_AfterSetNegativeFPS_ReturnsPreviousValue();

//     // ---------- setFPS ----------
//     void SetFPS_PositiveValue_FPSChanges();
//     void SetFPS_MultipleValidValues_UpdatesEachTime();
//     void SetFPS_ZeroValue_FPSDoesNotChange();
//     void SetFPS_NegativeValue_FPSDoesNotChange();
//     void SetFPS_MinimumValidValue_Updates();

//     // ---------- getFrameCount ----------
//     void GetFrameCount_DefaultSprite_ReturnsOne();
//     void GetFrameCount_AfterAddFrame_Increases();
//     void GetFrameCount_AfterDuplicateFrame_Increases();
//     void GetFrameCount_AfterRemoveFrame_Decreases();
// };

// // ========== IMPLEMENTATION ==========

// // ---------- constructor ----------

// void SpriteTest::Constructor_DefaultSprite_FrameCountIsOne()
// {
//     Sprite sprite;

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// void SpriteTest::Constructor_DefaultSprite_CurrentFrameIndexIsZero()
// {
//     Sprite sprite;

//     QCOMPARE(sprite.getCurrentFrameIndex(), 0);
// }

// void SpriteTest::Constructor_DefaultSprite_FPSIsDefault()
// {
//     Sprite sprite;

//     QCOMPARE(sprite.getFPS(), 12);
// }

// void SpriteTest::Constructor_DefaultSprite_FrameHasDefaultResolution()
// {
//     Sprite sprite;

//     Frame& frame = sprite.getCurrentFrame();

//     QCOMPARE(frame.width, 16);
//     QCOMPARE(frame.height, 16);
// }

// // ---------- addFrame ----------

// void SpriteTest::AddFrame_ValidFrame_FrameCountIncreases()
// {
//     Sprite sprite;
//     Frame frame;

//     sprite.addFrame(frame);

//     QCOMPARE(sprite.getFrameCount(), 2);
// }

// // ---------- removeFrame ----------

// void SpriteTest::RemoveFrame_ValidIndex_FrameCountDecreases()
// {
//     Sprite sprite;
//     Frame frame;

//     sprite.addFrame(frame);
//     sprite.removeFrame(1);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// void SpriteTest::RemoveFrame_OnlyFrame_FrameCountStaysOne()
// {
//     Sprite sprite;

//     sprite.removeFrame(0);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// void SpriteTest::RemoveFrame_OnlyFrame_CurrentFrameIndexStaysZero()
// {
//     Sprite sprite;

//     sprite.removeFrame(0);

//     QCOMPARE(sprite.getCurrentFrameIndex(), 0);
// }

// void SpriteTest::RemoveFrame_NegativeIndex_FrameCountDoesNotChange()
// {
//     Sprite sprite;

//     sprite.removeFrame(-1);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// void SpriteTest::RemoveFrame_IndexTooLarge_FrameCountDoesNotChange()
// {
//     Sprite sprite;

//     sprite.removeFrame(20);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// // ---------- duplicateFrame ----------

// void SpriteTest::DuplicateFrame_ValidIndex_FrameCountIncreases()
// {
//     Sprite sprite;

//     sprite.duplicateFrame(0);

//     QCOMPARE(sprite.getFrameCount(), 2);
// }

// void SpriteTest::DuplicateFrame_NegativeIndex_FrameCountDoesNotChange()
// {
//     Sprite sprite;

//     sprite.duplicateFrame(-1);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// void SpriteTest::DuplicateFrame_IndexTooLarge_FrameCountDoesNotChange()
// {
//     Sprite sprite;

//     sprite.duplicateFrame(20);

//     QCOMPARE(sprite.getFrameCount(), 1);
// }

// // ---------- moveFrame ----------
// // ---------- getCurrentFrame ----------
// // ---------- getCurrentFrameIndex ----------
// // ---------- getFrame ----------
// // MISSING IMPLEMENTATION OF SOME TESTS HERE.
// void SpriteTest::GetFrame_NegativeIndex_ThrowsException()
// {
//     Sprite sprite;

//     QVERIFY_THROWS_EXCEPTION(std::out_of_range, sprite.getFrame(-1));
// }

// void SpriteTest::GetFrame_IndexTooLarge_ThrowsException()
// {
//     Sprite sprite;

//     QVERIFY_THROWS_EXCEPTION(std::out_of_range, sprite.getFrame(20));
// }

// // ---------- getFPS ----------
// // ---------- setFPS ----------
// // ---------- getFrameCount ----------
