API Details
===========

Includes
-------------
[AdColonyAgent Class Reference](#adcolonyagent-class-reference)

[AdColonyAdsListener Class Reference](#adcolonyadslistener-class-reference)

* * * * *

[`AdColonyAgent Class Reference`](#adcolonyagent)
---------
- [`configure`](#configure)

   Configures AdColony specifically for your app; required for usage of
    the rest of the API.
- [`getAdsListener`](#getadslistener)

   Get AdColonyAdsListener.
- [`getCustomID`](#getcustomid)

   Returns the device's current custom identifier.
- [`getInstance`](#getinstance)

   Get the plugin instance.
- [`isReady`](#isReady)

   Returns whether or not a video is available in the specified zone.
- [`setAdsListener`](#setadslistener)

   set AdColonyAdsListener.
- [`setCustomID`](#setcustomid)

   Assigns your own custom identifier to the current app user.
- [`setDebugMode`](#setdebugmode)

   Set debug mode
- [`showV4VC`](#showv4vc)

   Plays an AdColony V4VC ad if one is available.
- [`showVideoAd`](#showvideoad)

   Plays an AdColony ad.
- [`statusForZone`](#statusforzone)

   Returns status of the AdColony zone passed in.

* * * * *

[`AdColonyAdsListener Class Reference`](#adcolonyadslistener)
----------------------------
- [`onAdColonyAdAttemptFinished`](#onadcolonyadattemptfinished)

   Notifies your app that an ad completed playing and control has been
    returned to the app
- [`onAdColonyAdAvailabilityChange`](#onadcolonyadavailabilitychange)

   Provides your app with real-time updates about ad availability
    changes
- [`onAdColonyAdStarted`](#onadcolonyadstarted)

   Notifies your app that an ad will actually play in response to the
    app's request to play an ad
- [`onAdColonyV4VCReward`](#onadcolonyv4vcreward)

   Notifies your app after an ad is displayed when a virtual currency
    transaction has completed

### AdColonyAgent

* * * * *

Initiate plugin

    AdColonyAgent();  

* * * * *

### configure

* * * * *

Configures AdColony specifically for your app; required for usage of the
rest of the API.

    void configure(
        const char *options,
        const char *appID,
        const std::vector<std::string>& zoneIDs,
        AdColonyAdsListener *listener);  

##### Parameters

  `options`

   A String containing your app version, and the origin store (example:
    “version:1.1,store:google”). Please note that if you are integrating
    into an Amazon app you will need to replace 'google' with 'amazon'
    in the client\_options String.

  `appID`

   The AdColony app ID for your app. This can be created and retrieved
    at the [Control Panel](http://clients.adcolony.com).

  `zoneIDs`

   An list of at least one AdColony zone ID string. AdColony zone IDs
    can be created and retrieved at the [Control
    Panel](http://clients.adcolony.com). If \`nil\`, app will be unable
    to play ads and AdColony will only provide limited reporting and
    install tracking functionality.

  `listener`

   The listener to receive V4VC and ad availability events. Can be
    \`NULL\` for apps that do not need these events.

* * * * *

### getAdsListener

* * * * *

Get AdColonyAdsListener.

    AdColonyAdsListener * getAdsListener();  

##### Return Value

AdColonyAdsListener.

* * * * *

### getCustomID

* * * * *

Returns the device's current custom identifier.

    std::string getCustomID();  

##### Return Value

The custom identifier string most recently set using \`setCustomID\`.

* * * * *

### getInstance

* * * * *

Get the plugin instance.

    static AdColonyAgent* getInstance();  

* * * * *

### isReady

* * * * *

Returns whether or not a video is available in the specified zone.

    bool isReady(
        const char *zoneID);  

##### Parameters
  `zoneID`

  The zone from which the ad should play.

* * * * *

### setAdsListener

* * * * *

set AdColonyAdsListener.

    void setAdsListener(
        AdColonyAdsListener *listener);  

##### Parameters

  `listener`

   The listener to receive V4VC and ad availability events. Can be
    \`NULL\` for apps that do not need these events.

* * * * *

### setCustomID

* * * * *

Assigns your own custom identifier to the current app user.

    void setCustomID(
        const char *customID);  

##### Parameters

  `customID`

   An arbitrary, application-specific identifier string for the current
    user. Must be less than 128 characters.

* * * * *

### setDebugMode

* * * * *

Set debug mode

    void setDebugMode(
        bool debug);  

##### Parameters

  `debug`

   Whether is debug mode.

* * * * *

### showV4VC

* * * * *

Plays an AdColony V4VC ad if one is available.

    void showV4VC(
        const char *zoneID,
        bool prePopup,
        bool postPopup);  

##### Parameters

  `zoneID`

   The zone from which the ad should play.

  `prePopup`

   Whether AdColony should display an instructional popup before the
    ad.

  `postPopup`

   Whether AdColony should display an instructional popup after the ad.

* * * * *

### showVideoAd

* * * * *

Plays an AdColony ad.

    void showVideoAd(
        const char *zoneID);  

##### Parameters

  `zoneID`

   The zone from which the ad should play.

* * * * *

### statusForZone

* * * * *

Returns status of the AdColony zone passed in.

    std::string statusForZone(
        const char *zoneID);  

##### Parameters

  `zoneID`

   The zone from which the ad should play.

##### Return Value

Returns one of the following strings:

-  "invalid" - You've entered an incorrect zone id, or AdColony has not been configured with that zone ID.
- "unknown" - Indicates that AdColony has not yet received the zone's configuration from the server.
- "off" - The zone is disabled. The zone has been turned off on the control panel.
- "loading" - Indicates that the zone is preparing ads for display. 
- "active" - The zone is enabled and has ads ready to be played.

 

* * * * *

AdColonyAdsListener
----------------------------
### onAdColonyAdAttemptFinished

* * * * *

Notifies your app that an ad completed playing and control has been
returned to the app

    virtual void onAdColonyAdAttemptFinished(
        bool adShown);

##### Parameters

  `adShown`

   Whether an ad was actually shown.

* * * * *

### onAdColonyAdAvailabilityChange

* * * * *

Provides your app with real-time updates about ad availability changes

    virtual void onAdColonyAdAvailabilityChange(
        bool success,
        const char *zoneID,
        const char *msg);

##### Parameters

  `success`

   whether or not ad is ready to play.

  `zoneID`

   The zone from which the ad should play.

  `msg`

   message.

* * * * *

### onAdColonyAdStarted

* * * * *

Notifies your app that an ad will actually play in response to the app's
request to play an ad

    void onAdColonyAdStarted();

* * * * *

### onAdColonyV4VCReward

* * * * *

Notifies your app after an ad is displayed when a virtual currency
transaction has completed

    void onAdColonyV4VCReward(
        bool success,
        const char *name,
        int points);

##### Parameters

  `success`

   Whether the transaction succeeded or failed.

  `name`

   The currency name.

  `points`

   The point number player has got.

* * * * *

