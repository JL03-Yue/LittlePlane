/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Little Plane", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add plane
    plane = Sprite::create("plane.jpg");
    if (plane == nullptr)
    {
        problemLoading("'plane.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        plane->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        plane->setScale(1/20.0);

        // add the sprite as a child to this layer
        this->addChild(plane, 1);
    }

    //add a touch event
    //  Create a "one by one" touch event listener
// (processes one touch at a time)
    auto planeListener = EventListenerTouchOneByOne::create();

    // trigger when you push down
    //use & to pass in params
    planeListener->onTouchBegan = [&](Touch* touch, Event* event) {
        log("onTouchBegan");
        //get the position of mouse
        Point pos1 = touch->getLocationInView();
        //transform to coco position
        Point pos2 = Director::getInstance()->convertToGL(pos1);

        // Move a sprite to a specific location over 1 seconds.
        auto moveTo = MoveTo::create(1, Vec2(pos2.x, pos2.y));
        
        plane->runAction(moveTo);
        return true; // if you are consuming it
    };

    // trigger when moving touch
    planeListener->onTouchMoved = [](Touch* touch, Event* event) {
    };

    // trigger when you let up
    planeListener->onTouchEnded = [=](Touch* touch, Event* event) {
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(planeListener,plane);

    //set time update
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::myUpdate), 0.1f);



    return true;
}

void HelloWorld::myUpdate(float fdelta)
{
    //log("myUpdate %f", fdelta);
    Point pos = plane->getPosition();

    // add plane
    auto bullet = Sprite::create("bullet.png");
    if (plane == nullptr)
    {
        problemLoading("'bullet.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        bullet->setPosition(pos);
        bullet->setScale(1 / 15.0);

        // bullet under the plane
        this->addChild(bullet, 0);
    }

    //move the bullet up relatively by moveBy

    auto moveBy = MoveBy::create(2, Vec2(0, 800));

    bullet->runAction(moveBy);


}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
