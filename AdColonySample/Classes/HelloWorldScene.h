#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AdColonyAgent.h"

class HelloWorld : public cocos2d::Layer, public AdColonyAdsListener{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void testShow(Ref* pSender);
    void testShowV4VC(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
   //callback for AdColony
   void onAdColonyAdAvailabilityChange(bool success, const char* zoneID, const char* msg);
   void onAdColonyV4VCReward(bool success, const char* name,int points);
  
   void onAdColonyAdStarted();
   void onAdColonyAdAttemptFinished(bool adShown);

private:
    AdColonyAgent* _adcolonyAds;
    //MyAdColonyAdsListener *_listener;
    cocos2d::MenuItemLabel* _pItemInterstitialTest;
    cocos2d::MenuItemLabel* _pItemV4VCTest;
    cocos2d::CCLabelTTF* _labelVCAmount;
    int _creditAmount;
  void logZoneStatus();
};

#endif // __HELLOWORLD_SCENE_H__
