adcolony_cocos2dx
=================
Cocos2d-x support for AdColony.

* Modified: March 13th, 2015
* Plug-in Version: 0.9.0
* iOS SDK Version: 2.5.0
* Android SDK Version: 2.2.1

##Contents##
* [About](#about)
* [Run Sample](#run-sample)
* [Integrate AdColony to your Cocos2d-x Application](#integrate-adcolony-to-your-cocos2d-x-application)
    * [Install Plugin](#install-plugin)
    * [Setup AdColony plugin](#setup-adcolony-plugin)
    * [Showing Interstitial Videos](#showing-interstitial-videos)
    * [Showing V4VC Videos](#showing-v4vc-videos)

About
=====
--------

このドキュメントはcocos2d-xで開発したアプリケーションにAdColony SDKを導入する際の手順書です。このドキュメントは下記開発環境を想定しています。

* Cocos2d-x バージョン: 3.0+
* 開発言語: C++
* iOS開発IDE: Xcode
* Android開発IDE: Eclipse

Run Sample
==========
-----------------
* submoduleをインストールする

        git submodule update --init --recursive

*  cocos2dxが依存してるpackageをダウンロードする

        cd AdColonySample/cocos2d
        ./download-deps.py

* `adcolony` ディレクトリー を `AdColonySample/cocos2d/plugin/plugins/`の下にコピーしてください。

        cp -a ./adcolony AdColonySample/cocos2d/plugin/plugins/

iOSで実行する場合
---------------
* Open `AdColonySample/proj.ios/AdColonySample.xcodeproj`
* Build and run on iOS

Androidで実行する場合
---------------------
* pluginをビルドする

        cd AdColonySample/cocos2d/plugin/tools/
        ./publish.sh
        ./gameDevGuide.sh

* プロジェクトをEclipseにインポート
    * cocos2dライブラリーをインポート
        * `AdColonySample/cocos2d/cocos/platform/android/java`ディレクトリーからインポートしてください。
    * サンプルプロジェクトをインポート
        * `AdColonySample/proj.android`ディレクトリーからインポートしてください。
* 環境変数を設定
    * C/C++ 環境変数 `NDK_ROOT`の設定:
        * Eclipse->Preferences->C/C++->Build->**Environment**を開く
        * **Add**をクリックして"name"に`NDK_ROOT`、"value"にNDK実際のパスに設定しくてください。

* Google Play Serviceをリンクする

    AdColony SDK は`Google play service` API を使ってIDFAを取得してコンバージョンしています.下記のようにプロジェクトに"Google Play services"をリンクしてください。 

    * `Google Play services` ライブラリープロジェクトをワークスペースに導入する。
    * プロジェクトを選択し、右クリックして 「Android」を選択します。
    * "Add" クリックして開いたウィンドウに`Google Play services` プロジェクトを選択します。

    **Note:** `Google Play Service`の利用には、Android 2.3以上が必要になります、詳細についてはここをチェックをしてください。 [http://developer.android.com/intl/ja/google/play-services/setup.html](http://developer.android.com/intl/ja/google/play-services/setup.html)

* AdColonySampleプロジェクトをビルドして実行

    
Integrate AdColony to your Cocos2d-x Application
=====================================
----------------------------------------------------------------
Install Plugin
=======
* `adcolony` ディレクトリー を `[your_project_path]/cocos2d/plugin/plugins/`の下にコピーしてください。

iOS
----
* Xcodeプロジェクトにプラグインを追加
    * `Xcode->File->Add Files to "yourProject"`を開く
        * `cocos2d/plugin/protocols/proj.ios/PluginProtocol.xcodeproj`をプロジェクトに追加してください。
        * `cocos2d/plugin/plugins/adcolony/proj.ios/Pluginadcolony.xcodeproj`プロジェクトに追加してください。
        ![](./images/add_plugin_to_xcode.png)

* ターゲットを選択して、`Build Phases->Target Dependencies`に下記を追加してください。
    * Pluginadcolony
    * PluginProtocol
* ターゲットを選択して、`Build Phases->Link Binary With Libraries`に下記を追加してください。
    * libPluginProtocol.a
    * libPluginAdColony.a
    * frameworks
        * `libz.1.2.5.dylib`
        * `AdColony.framework`  (`+`->`Add Other...`->`cocos2d/plugin/plugins/adcolony/proj.ios/AdColony.framework`)
        * `AdSupport.framework (Set to Optional)`
        * `AudioToolbox.framework`
        * `AVFoundation.framework`
        * `CoreGraphics.framework`
        * `CoreMedia.framework`  
        * `CoreTelephony.framework`
        * `EventKit.framework`
        * `EventKitUI.framework`
        * `MediaPlayer.framework`
        * `MessageUI.framework`
        * `QuartzCore.framework`
        * `Social.framework` (Set to Optional)
        * `StoreKit.framework` (Set to Optional)
        * `SystemConfiguration.framework
        * `WebKit.framework` (Set to Optional)

* `Build Settings`に下記を設定してください。
    * `Header Search Paths`に下記を追加してください。
        * `$(SRCROOT)/../cocos2d/plugin/protocols/include`
        * `$(SRCROOT)/../cocos2d/plugin/plugins/adcolony/include`
    * `Linking-Other Linker Flags`に下記を追加してください。
        * `-force_load $(BUILT_PRODUCTS_DIR)/libPluginAdColony.a`
        * `-force_load $(SRCROOT)/../cocos2d/plugin/plugins/adcolony/proj.ios/AdColony.framework/AdColony`
        * `-fobjc-arc` 

        **注意**:  `-ObjC`が設定された場合、`-force_load` を設定する必要がないです。

Android
-------
(Based on Eclipse)

* pluginをビルドする
    * コンパイルフラグを設定する
        `[your_project_path]/proj.android/jni/Application.mk`ファイルに、`APP_STL` を確認してください。
    
            APP_STL := c++_static #or gnustl_static
    
    `[your_project_path]/cocos2d/plugin/plugins/adcolony/proj.android/jni/Application.mk`を開いて`APP_STL`を下記の設定と同じ値を設定してください。
    * config.shを設定する( cocos2d-x version < 3.3 )
        * `[your_project_path]/cocos2d/plugin/tools/config.sh`ファイルを開いて、`ALL_PLUGINS`に`adcolony`を追加してください。

                #define plugins array 
                export ALL_PLUGINS=("adcolony")

        * AdColonyプラグインをビルドする。

                cd [your_project_path]/cocos2d/plugin/tools/
                ./publish.sh
                ./gameDevGuide.sh # adcolonyを選択してください。

    * Manifestを修正する
        
        gameDevGuide.sh既に"AndroidManifest.xml"を修正しました、下記のコードが`<application...>`タグの前に追加されているのを確認してください：

            <uses-permission android:name="android.permission.INTERNET" />
            <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" /> 
            <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
            <uses-permission android:name="android.permission.VIBRATE" />
        
        下記のコードがapplicationタグに追加しました:

            <activity android:name="com.jirbo.adcolony.AdColonyOverlay"
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" />
            
            <activity android:name="com.jirbo.adcolony.AdColonyFullscreen"
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:theme="@android:style/Theme.Black.NoTitleBar.Fullscreen" />
            
            <activity android:name="com.jirbo.adcolony.AdColonyBrowser"
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:theme="@android:style/Theme.Black.NoTitleBar.Fullscreen" />
        
        Dynamic End Cardのパフォーマンスを最適化するために、下記のようにハードウェアアクセラレーションを有効にしてください。
            
            android:hardwareAccelerated="true"
    注意: アプリがAPI レベル13以下に対応している場合、上記configChanges設定からscreenSizeを消してください。

* Plugin-xを初期化するコードを`proj.android/src/org/cocos2dx/cpp/AppActivity.java`と記述してください。

        import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
        import org.cocos2dx.plugin.PluginWrapper;
        
        public Cocos2dxGLSurfaceView onCreateView() {
            Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
            // TestCpp should create stencil buffer
            glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
            //initiate plugin-x
            PluginWrapper.init(this);
            PluginWrapper.setGLSurfaceView(glSurfaceView);
            return glSurfaceView;
        }
    
* Java VMの設定 
   * `proj.android/jni/hellocpp/main.cpp`を開く。
    * ヘッダーファイルをインポート
    
            #include "PluginJniHelper.h"

    * 下記のようにJava VMをセットしてください。

            void cocos_android_app_init (JNIEnv* env, jobject thiz) {
                LOGD("cocos_android_app_init");
                AppDelegate *pAppDelegate = new AppDelegate();
                // plugin-x
                JavaVM* vm;
                env->GetJavaVM(&vm);
                PluginJniHelper::setJavaVM(vm);
            }
* `Adroind.mk`にAdColony plugin関係あるファイルを記述 ( `[your_project_path]/proj.android/jni/Android.mk` )
 
        `gameDevGuide.sh`既に`Android.mk`を修正しました、下記のコードが追加されているのを確認してください：

            $(call import-add-path,$(LOCAL_PATH)/../../cocos2d/plugin/publish)
            
            LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic
            LOCAL_WHOLE_STATIC_LIBRARIES += PluginAdColonyStatic
            
            $(call import-module,plugins/adcolony/android)

    例:
 
    ![](./images/Android_mk_snapshot.png)

* Google Play Serviceをリンクする

    AdColony SDK は`Google play service` API を使ってIDFAを取得してコンバージョンしています.下記のようにプロジェクトに"Google Play services"をリンクしてください。 

    * `Google Play services` ライブラリープロジェクトをワークスペースに導入する。
    * プロジェクトを選択し、右クリックして 「Android」を選択します。
    * "Add" クリックして開いたウィンドウに`Google Play services` プロジェクトを選択します。
    * AndroidManifest.xmlを開いて、`<application>` タグの間に下記を確認してください。なかったら追加してください。
     
        <meta-data  android:name="com.google.android.gms.version"  android:value="@integer/google_play_services_version" />

    **Note:** `Google Play Service`の利用には、Android 2.3以上が必要になります、詳細についてはここをチェックをしてください。 [http://developer.android.com/intl/ja/google/play-services/setup.html](http://developer.android.com/intl/ja/google/play-services/setup.html)


注意: アプリがAPI レベル13以下に対応している場合、 `[your_project_path]/proj.android/AndroidManifest.xml`ファイルの中にconfigChanges設定からscreenSizeを消してください。


Setup AdColony plugin
=========================

Include header files and namespaces
------------------------------------------------

* ヘッダーファイルをインポート

        #include "AdColonyAgent.h"

* use cocos2d::plugin namespace

        USING_NS_CC;
        using namespace cocos2d::plugin;
    

Configure AdColony
-------------------------

AdColony Pluginをロードして下記のように必要の情報を設定してください。

    //Load plugin
    AdColonyAgent* _adcolonyAds = AdColonyAgent::getInstance();
    //set custom id, used for V4VC
    _adcolonyAds->setCustomID("customID");
    //configure adcolony
    std::vector<std::string> zoneIDs =  { "zone_id_1", "zone_id_2"};
    _adcolonyAds->configure("options", "appID", zoneIDs, listener);

- **customID**

    ユーザ識別子(custom identifier)を設定してください。これは毎回リワードコールバックするときにアプリのサーバ側にも送信されます。これを使用することで、通貨を付与するユーザを特定することができます。V4VCの場合設定してください。
- **opntions**

    アプリのバージョンとストア情報を設定してください (例: “version:1.1,store:google”). Amazonストアに出す場合ストアは 'google' ではなく 'amazon' 設定してください。iOSの場合、store情報はなくていいです。
- **appID**

    AdColony app ID。
- **zoneIDs**

    枠IDリスト。
- **listener**

    AdColony SDKから通知を受けるためのAdColonyAdsListenerを登録してください。

listenerの例(AdColonySampleから）

    /* HelloWorldScene.h */

    #include "AdColonyAgent.h"

    class HelloWorld : public cocos2d::Layer, public AdColonyAdsListener{
    public:
       //callback for AdColony
       void onAdColonyAdAvailabilityChange(bool success, const char* zoneID, const char* msg);
       void onAdColonyV4VCReward(bool success, const char* name,int points);
       void onAdColonyAdStarted();
       void onAdColonyAdAttemptFinished(bool adShown);

    /* HelloWorldScene.cpp */
    void HelloWorld::onAdColonyAdAvailabilityChange(bool success, const char* zoneID, const char* msg)
    {
      log("onAdColonyAdAvailabilityChange, success : %d, zoneID: %s msg : %s", success, zoneID, msg);

      if (success) {
        if (strcmp(zoneID, AdColony_Interstitial_Zone_ID) == 0) {
          //intersttial zone is ready for show
        } else if (strcmp(zoneID, AdColony_V4VC_Zone_ID) == 0) {
          //V4VC is ready to show
        }
      }
    }

    void HelloWorld::onAdColonyV4VCReward(bool success, const char* name,int points)
    {
      log("onAdColonyV4VCReward, success:%d name:%s points:%d", success, name, points);

      if(success){
        //get reward successfully
      }
    }

    void HelloWorld::onAdColonyAdStarted()
    {
      log("onAdColonyV4VCReward");
    }

    void HelloWorld::onAdColonyAdAttemptFinished(bool adShown)
    {
      log("onAdColonyAdAttemptFinished adShown:%d", adShown);
    }


Showing interstitial Videos
=================
動画成功にロードした後に下記のようにインタスティシャール広告を表示してください:

    _adcolonyAds->showVideoAd("zoneID");

- **zoneID**

    configureで設定されてるIDリスト中にある管理画面で取得した有効なインタスティシャール枠IDです。

Showing V4VC Videos
===============
AdColony V4VC (Videos-for-Virtual-Currency)は[[interstitial ads|AdColony Product Overview]]の上で実装した動画広告を再生完了した時点で、ユーザーに仮想通貨を付与することができるシステムです。AdColony V4VCはユーザーの仮想通貨残高を追跡しません。ユーザーに仮想通貨を付与すべき時点でアプリケーションに通知する機能を提供しています。

クライアント側で仮想通貨の残高を管理してるアプリには、V4VCのクライアントモードで簡単に実装できます。サーバー側で仮想通貨の残高を管理してる場合、V4VCはよりセキュリティーの高いサーバー側モードによって、付与する時点でサーバーに通知することも可能です。

Client-side Mode Instructions
--------------------------------------
先に[[Configure AdColony]]を実装してください。クライアントモードは [[Showing-Interstitial-Videos]]の実装する方法とほぼ同様であり、いくつかの機能が追加されます。

1. Glossomにてapp ID、zone IDの発行しお渡し致します。 
2. 枠の設定ページの"Virtual Currency Rewards" を有効にして、currency name と reward amount　を設定してください。
3. アプリ起動するところにAdColonyの設定関数（configure）でapp ID, zone ID, an AdColonyDelegateを設定してください。
4. `AdColonyAdsListener` V4VCリワードコールバックを実装してください。その中でユーザーの仮想通貨の残高とそのUIを更新してください。
5. AdColonyのV4VCの動画広告とポップアップメッセージを表示するコードを実装してください。

        _adcolonyAds->showV4VC("zoneID", prePopup, postPopup);

    - **zoneID**

        configureで設定されてるIDリスト中にある管理画面で取得した有効なV４VC枠IDです。
    - **prePopup**

       動画表示前の確認メッセージを表示するかどうか、表示したい場合trueに設定してください。
    - **postPopup**

        動画表示後の確認メッセージを表示するかどうか、表示したい場合trueに設定してください。

**Code Example - AdColonySample App**

- クライアントモードでのV4VC広告の実装については、サンプルアプリAdColonySampleを参照してくささい。

Server-side Mode Instructions
---------------------------------------
サーバ側モードはAdColonyはアプリに仮想通貨をリワードする通知を行う前に、アプリのサーバー側に先に通知する以外はクライアント側モードとほぼ同じです。AdColonyはアプリのサーバーにユーザーとリワードを含めて様々な情報を渡します。それをもってサーバー側がそのリワードを認証または否認証することができます。この方式を実装するにはクライアントモード手順を実装した上に、下記を実装してください。

1. `AdColonyAdsListener` V4VC のリワードコールバックを実装してアプリサーバーからもらった仮想通貨の情報を更新してください。
2. AdColony SDKにユーザ識別子(custom identifier)を設定してください。これは毎回リワードコールバックするときにアプリのサーバ側にも送信されます。これを使用することで、通貨を付与するユーザを特定することができます。
3.Glossomにてzoneのサーバ側V4VCを有効にし、ポストバック用のURLを設定致します。
4. ポストバック先のURL実装、そして有効なレスポンスをしてください。

Code Example - Custom ID
-----------------------------------
ユーザーを識別するために、カスタマイズユーザーIDを設定してください。よく使われるのはvendor identifier、開発者ごとに固有のものであります。

1. AdColonyのアカウント情報を設定する*前*に、`_adcolonyAds->setCustomID("customID")`を呼び出してユーザーIDを設定してください。このIDはサーバーとのすべてのコミュニケーションに使用されます。
2. Zoneの設定画面でコールバックURLの最後に `&custom_id=[CUSTOM_ID]` を追加してください。

Code Example - Server-side Callback
-------------------------------------------------
server-side V4VCを設定したzoneを利用の場合、ポストバック先のURLは有効なレスポンスをするため、下記の手順を従って確認してください。

1. URLパラメーターを読んで発行されたzoneの秘密鍵を使って発行したかどうかを確認してください。
2. パラメーターに含まれたユーザーIDは有効であるかどうかを確認してください。
3. 重複チェックを行って、ユーザーに指定したアマウントとタイプの通貨を付与してください。
4. 上記を踏まえて、有効なレスポンスをリターンしてください。

AdColonyからコールバックするURLの仕様は下記でございます。括弧内に囲まれているパラメータはアプリケーション実装時の情報により動的にセットされます。

```
[http://www.example.com/anypath/callback_url.php]?id=[transaction id]&uid=[AdColony device id]&amount=[currency amount to award]&currency=[name of currency to award]&open_udid=[OpenUDID]&udid=[UDID]&odin1=[ODIN1]&mac_sha1=[SHA-1 of MAC address]&verifier=[security value]
```

URL Parameter | Type | Purpose
--- | --- | ---
id | Positive long integer | Unique V4VC transaction ID
uid | String | AdColony device ID
amount | Positive integer | Amount of currency to reward
currency | String | Name of currency to reward
open_udid | String | OpenUDID
udid | String | Apple UDID
odin1 | String | Open Device Identification Number (ODIN)
mac_sha1 | String | SHA-1 hash of lowercase colon-separated MAC address
custom_id | String | Custom user ID
verifier | String | MD5 hash for message security

参考例：下記はPHP + MySQLで実装した例です

```php
<?php
    $MY_SECRET_KEY = "This is provided by adcolony.com and differs for each zone";

    $trans_id = mysql_real_escape_string($_GET['id']);
    $dev_id = mysql_real_escape_string($_GET['uid']);
    $amt = mysql_real_escape_string($_GET['amount']);
    $currency = mysql_real_escape_string($_GET['currency']);
    $open_udid = mysql_real_escape_string($_GET['open_udid']);
    $udid = mysql_real_escape_string($_GET['udid']);
    $odin1 = mysql_real_escape_string($_GET['odin1']);
    $mac_sha1 = mysql_real_escape_string($_GET['mac_sha1']);
    $custom_id = mysql_real_escape_string($_GET['custom_id']);
    $verifier = mysql_real_escape_string($_GET['verifier']);

    //verify hash
    $test_string = "" . $trans_id . $dev_id . $amt . $currency . $MY_SECRET_KEY . 
        $open_udid . $udid . $odin1 . $mac_sha1 . $custom_id;
    $test_result = md5($test_string);
    if($test_result != $verifier) {
        echo "vc_noreward";
        die;
    }
    
    $user_id = //TODO: get your internal user id using one of the supplied identifiers
    // OpenUDID, AdColony ID, ODIN1, custom ID can be accessed via a method call in the AdColony client SDK

    //check for a valid user
    if(!$user_id) {
        echo "vc_noreward";
        die;
    }
    //insert the new transaction
    $query = "INSERT INTO AdColony_Transactions(id, amount, name, user_id, time) ".
        "VALUES ($trans_id, $amt, '$currency', $user_id, UTC_TIMESTAMP())"; 
    $result = mysql_query($query);
    if(!$result) {
        //check for duplicate on insertion
        if(mysql_errno() == 1062) {
            echo "vc_success";
            die;
        }
        //otherwise insert failed and AdColony should retry later
        else {
            echo "mysql error number".mysql_errno();
            die;
        }
    }
    //TODO: award the user the appropriate amount and type of currency here
    echo "vc_success";
?>
```
注意、`TODO`のところにはアプリケーション特定のロジックを実装してください。上記のコードで使ったMySQLデータベースは下記のSQLで作成できます。(通貨名を`enum`にインサートするのを忘れないようにして下さい)

```mysql
CREATE TABLE `AdColony_Transactions` (
  `id` bigint(20) NOT NULL default '0',
  `amount` int(11) default NULL,
  `name` enum('Currency Name 1') default NULL,
  `user_id` int(11) default NULL,
  `time` timestamp NULL default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
