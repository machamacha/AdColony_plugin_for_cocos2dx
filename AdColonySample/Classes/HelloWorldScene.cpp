#include "HelloWorldScene.h"

//define account info for adcolony
//iOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define AdColony_App_ID "appbdee68ae27024084bb334a"
#define AdColony_Interstitial_Zone_ID "vzf8fb4670a60e4a139d01b5"
#define AdColony_V4VC_Zone_ID "vzf8e4e97704c4445c87504e"
#define AdColony_Client_Option "version:1.0,store:itunes"
//Android
#else
#define AdColony_App_ID "app185a7e71e1714831a49ec7"
#define AdColony_Interstitial_Zone_ID "vz06e8c32a037749699e7050"
#define AdColony_V4VC_Zone_ID "vz1fd5a8b2bf6841a0a4b826"
#define AdColony_Client_Option "version:1.0,store:google"
#endif

USING_NS_CC;
using namespace cocos2d::plugin;

Scene* HelloWorld::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("AdColony Sample for Cocos2d-x",
			"fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height
							- label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//add test menu
	Point beginPos = Point(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2 + 30);

	CCLabelTTF *labelInterstitialTest = CCLabelTTF::create("Loading Interstitial Ads...", "Arial", 50);
	_pItemInterstitialTest = MenuItemLabel::create(labelInterstitialTest,
			CC_CALLBACK_1(HelloWorld::testShow, this));
	_pItemInterstitialTest->setAnchorPoint(Point(0.5f, 0));
	_pItemInterstitialTest->setColor(ccc3(200, 0, 0));
	menu->addChild(_pItemInterstitialTest, 0);
	_pItemInterstitialTest->setPosition(beginPos);

	LabelTTF* labelV4VCTest = LabelTTF::create("Loading V4VC Ads...", "Arial", 50);
	_pItemV4VCTest = MenuItemLabel::create(labelV4VCTest,
			CC_CALLBACK_1(HelloWorld::testShowV4VC, this));
	_pItemV4VCTest->setAnchorPoint(Point(0.5f, 0));
	_pItemV4VCTest->setColor(ccc3(200, 0, 0));
	menu->addChild(_pItemV4VCTest, 0);
	_pItemV4VCTest->setPosition(Point(beginPos.x, beginPos.y - 100));

	//get accumulated total amount of virtual currency.
	UserDefault *_userDef = UserDefault::getInstance();
	_creditAmount =_userDef->getIntegerForKey("vc_amount");
	CCString* str = CCString::createWithFormat("credits: %d", _creditAmount);
	_labelVCAmount = CCLabelTTF::create(str->getCString(), "Arial", 30);
	_labelVCAmount->setColor(ccc3(255, 255, 255));
	_labelVCAmount->setPosition(CCPointMake(beginPos.x, beginPos.y - 120));
	addChild(_labelVCAmount);

	_adcolonyAds = AdColonyAgent::getInstance();

	//only for showing more debug logs!If you want to turn on or off debug mode, contact us!
	_adcolonyAds->setDebugMode(true);

	//Sets a custom ID String that is passed through to server-­side V4VC callbacks
	//
	// _adcolonyAds->setCustomID("user_id1234");
	//
	//it is optional, but must be called before configure()

	//configure AdColony once early before any other AdColony calls (except setCustomID/setDeviceID).
	std::vector<std::string> zoneIDs = {AdColony_Interstitial_Zone_ID, AdColony_V4VC_Zone_ID};
	_adcolonyAds->configure(AdColony_Client_Option, AdColony_App_ID, zoneIDs, this);

	return true;
}


void HelloWorld::testShow(Ref* pSender) {
	if (_adcolonyAds) {
		_adcolonyAds->showVideoAd(AdColony_Interstitial_Zone_ID);
	}
}

void HelloWorld::testShowV4VC(Ref* pSender) {
	if (_adcolonyAds) {
		_adcolonyAds->showV4VC(AdColony_V4VC_Zone_ID, true, true);
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::onAdColonyAdAvailabilityChange(bool success, const char* zoneID, const char* msg)
{
  log("onAdColonyAdAvailabilityChange, success : %d, zoneID: %s msg : %s", success, zoneID, msg);

  if (success) {
    if (strcmp(zoneID, AdColony_Interstitial_Zone_ID) == 0) {
      LabelTTF* label = LabelTTF::create("Show Interstitial Ads", "Arial", 50);
      _pItemInterstitialTest->setLabel(label);
      _pItemInterstitialTest->setColor(ccc3(0, 255, 0));
    } else if (strcmp(zoneID, AdColony_V4VC_Zone_ID) == 0) {
      LabelTTF* label = LabelTTF::create("Show V4VC Ads", "Arial", 50);
      _pItemV4VCTest->setLabel(label);
      _pItemV4VCTest->setColor(ccc3(0, 254, 0));
    }
  }
}

void HelloWorld::onAdColonyV4VCReward(bool success, const char* name,int points)
{
  log("onAdColonyV4VCReward, success:%d name:%s points:%d", success, name, points);

  if(success){
    _creditAmount += points;
    UserDefault *_userDef = UserDefault::getInstance();
    _userDef->setIntegerForKey("vc_amount", _creditAmount);
    
    CCString* str = CCString::createWithFormat("credits: %d", _creditAmount);
    _labelVCAmount->setString(str->getCString());
  }
}

void HelloWorld::onAdColonyAdStarted()
{
  log("onAdColonyAdStarted");
}

void HelloWorld::onAdColonyAdAttemptFinished(bool adShown)
{
  log("onAdColonyAdAttemptFinished adShown:%d", adShown);
}
