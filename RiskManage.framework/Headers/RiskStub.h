//
//  RiskManage.h
//  RiskManage
//
//  Created by bigdog on 2018/12/17.
//  Copyright © 2018年 bangcle. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for RiskManage.
FOUNDATION_EXPORT double BCERiskManageVersionNumber;

//! Project version string for RiskManage.
FOUNDATION_EXPORT const unsigned char BCERiskManageVersionString[];

NS_ASSUME_NONNULL_BEGIN

////online structure
typedef NSURLSessionAuthChallengeDisposition (^BCERiskURLSessionDidReceiveAuthenticationChallengeBlock)
(NSURLSession * __nullable session,
 NSURLAuthenticationChallenge * __nullable challenge,
 NSURLCredential * _Nullable __autoreleasing * _Nullable credential);

typedef enum{
    kRiskCheckTypeUdid,
    kRiskCheckTypeDevInfo,
    kRiskCheckTypeApkInfo,
    kRiskCheckTypeStartInfo,
    kRiskCheckTypeStart,
    kRiskCheckTypeCrash,
    kRiskCheckTypeEmulator,
    kRiskCheckTypeLocation,
    kRiskCheckTypeRoot,
    kRiskCheckTypeHostFraud,
    kRiskCheckTypeDevices_Reuse,
    kRiskCheckTypeInject,
    kRiskCheckTypeDebugger,
    kRiskCheckTypeHttpProxy,
    kRiskCheckTypeVpnProxy,
    kRiskCheckTypeEnvCheck,
    kRiskCheckTypeMultiMessage,
    kRiskCheckTypeScreenSharing,
    kRiskCheckTypeResign,
    kRiskCheckTypeHttps,
    kRiskCheckTypeMacOS,
    kRiskCheckTypeTrollStore,
    kRiskCheckTypeAutoClick,
    kRiskCheckTypeRemoteControl,
    kRiskCheckTypeFacetimeCalling,
    kRiskCheckTypeUnknown
} BCERiskCheckType;
typedef void (^BCECallBack)(NSDictionary * _Nullable dictionary,BCERiskCheckType modularType);

////offline structure
typedef enum {
    kRiskEventUdid, //0
    kRiskEventRoot,
    kRiskEventEmulator,
    kRiskEventInject,
    kRiskEventDebug,
    kRiskEventHttpProxy,
    kRiskEventRiskFrame
} BCERiskEvent;

typedef enum {
    kRiskActionMessage, // 只提示
    kRiskActionMessageThenQuit, // 提示后强制退出
    kRiskActionQuitOrMessage, // 提示后选择退出
    kRiskActionQuit // 直接强退
} BCERiskAction;

typedef void (^BCERiskEventHandler)(NSDictionary * _Nullable data, BCERiskEvent riskType);
typedef void (^BCERiskDeviceCallback)(BOOL isRiskDevice, NSString *udid);

@interface BCEAlertContext : NSObject
@property (readonly) NSString* message; // 配置的策略弹框的内容
@property (readonly) NSString* title;  // 配置的策略弹框的标题
@property (readonly) BCERiskAction action; // 配置的策略类型
@end

@interface RiskStub : NSObject
////online feature
/// 不带返回初始化失败错误码的初始化方法（与带返回初始化失败错误码的初始化方法三选一即可）
/// @param key 初始化SDK所需的key
+ (void)initBangcleEverisk:(NSString *_Nonnull)key;

/// 带返回初始化失败错误码的初始化方法（与不带返回初始化失败错误码的初始化方法三选一即可）
/// @param key 初始化SDK所需的key
/// @return 初始化SDK的返回码
/// 0：表示初始化成功
/// 101: 表示初始化了多次
/// 102：key解析失败
/// 104：缺少EveriskResource.bundle资源包
+ (NSInteger)initBangcleEveriskWithKey:(NSString *_Nonnull)key;

/// 带返回初始化失败错误码的初始化方法，与上面两个初始化方法功能一样，使用任意一个即可；
/// 使用此方法不用单独再调用注册数据回调方法
/// @param key 初始化SDK所需的key
/// @param listener 数据回调
/// /// 0：表示初始化成功
/// 101: 表示初始化了多次
/// 102：key解析失败
/// 104：缺少EveriskResource.bundle资源包
+ (NSInteger)initBangcleEveriskWithKey:(NSString *_Nonnull)key withDataCallback:(BCECallBack _Nullable)listener;

/// 在线探针注册数据回调方法（可选接口）
/// @param listener 数据回调
+ (void)registerServiceWithDataBlock:(BCECallBack _Nullable )listener;

// call setLoginInfo in customer login event process block,
+ (void)setLoginInfo:(NSString*) info;

// call addTouchData in user touch event, optional
+ (void)addTouchData:(float) pointX withPointY:(float)pointY withSize:(float)size withPressue:(float)pressure;

/// 探针进入后台模式，进入此模式探针会暂停运行（APP切换后台时建议调用此方法，可选接口）
+ (void)appEnterBackground;

/// 探针进入前台模式，进入此模式探针会继续运行（APP切换前台时建议调用此方法，可选接口）
+ (void)appEnterForeground;

/// 添加用户信息接口（可选接口，非必要不调用）
/// @param key 添加用户信息的key
/// @param value 添加用户信息的value
/// @return 是否添加成功
+ (BOOL)addExtraUserData:(NSString *_Nonnull)key withUserDatavalue:(NSString *_Nonnull)value;

/// 添加用户信息接口（可选接口，非必要不调用）
/// @param jsonData 字典类型的用户信息
/// @return 是否添加成功
+ (BOOL)addExtraUserData:(NSDictionary *_Nonnull)jsonData;

/// 添加地理位置信息接口（可选接口，非必要不调用）
/// @param locationData 字典类型的地理位置信息
/// @return 是否添加成功
+ (BOOL)addExtraLocation:(NSDictionary *_Nonnull)locationData;

/// 添加用户ID（可选接口，非必要不调用）
/// @param value 用户id
+ (BOOL)addExtraUserID:(NSString *_Nonnull)value;

/// 添加用户ID相关信息（可选接口）
/// @param jsonData 字典类型的用户信息
/// @return 是否添加成功
+ (BOOL)addExtraUserIDWithDictionary:(NSDictionary *_Nonnull)jsonData;

/// 添加使用场景信息
/// @param userScenario 用户信息
+ (void)addUserScenario:(NSDictionary *_Nonnull)userScenario;

/**
  允许威胁感知主动请求位置权限，默认不请求位置权限。（如果需要调用此接口，须在SDK初始化之前调用）
 */
+ (void)allowBangcleGetLocationPermission;

/**
  允许威胁感知获取应用列表，默认不获取。（如果需要调用此接口，须在SDK初始化之前调用）
 */
+ (void)allowBangcleGetAppListPermission;

/**
  加解密方式改为国密加密（sm4），默认加解密方式为国际加密（AES+3DES）。（如果需要调用此接口，须在SDK初始化之前调用）
 */
+ (void)changeEncryptTypeToSm4;

/// 检测模拟器状态
+ (NSDictionary *)checkEmulatorStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测https劫持状态
+ (NSDictionary *)checkHttpsStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测http代理状态
+ (NSDictionary *)checkHttpProxyStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测越狱状态
+ (NSDictionary *)checkRootStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测框架软件
+ (NSDictionary *)checkRiskFrameStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测vpn代理状态
+ (NSDictionary *)checkVpnProxyStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检测macOS环境
+ (NSDictionary *)checkMacOSStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/**
  返回checker是否初始化成功
 */
+ (NSDictionary *_Nonnull)checkerInitialStatus;

/// 获取风险信息
+ (NSDictionary * _Nonnull)getRiskInfo;

/// 获取root信息
+ (NSDictionary *_Nullable)getRootInfo; //return nil if not root, return root info if the system with root

/// 获取模拟器信息
+ (NSDictionary *_Nullable)getEmulatorInfo; //return nil if run on real machine, return emulator info if run on emulator

/// 更新地理位置
/// @param country 国家
/// @param province 省份
/// @param city 城市
+ (void)updateLocation:(NSString * _Nonnull)country withProvince:(NSString*_Nonnull)province withCity: (NSString*_Nonnull)city;

/// 获取探针的版本号（可选接口，建议用下面的）
+ (NSString *)getEveriskVersion;

/// 获取探针的版本号（可选接口）
+ (NSString *)getEveriskSdkVersion;

/// 允许探针输出log（可选接口）
+ (void)enableBangcleLog;

/// 获取设备的UUID（可选接口）
+ (NSString *_Nullable)getEveriskUdid;

/// 获取探针的token（可选接口）
+ (NSDictionary *_Nullable)getEveriskToken;

/// 添加探针的服务器地址（可选接口）
/// @param downloadUrls 热更新地址（iOS版已废弃）
/// @param businessUrls 业务地址
+ (void)addUrl:(NSArray * _Nonnull )downloadUrls withBusinessUrl:(NSArray*_Nonnull)businessUrls;

/// 屏幕共享检测功能开关
/// @param enabled YES为开启，NO为关闭，默认值是YES
+ (void)setScreenSharingCheckerEnabled:(BOOL)enabled;

/// 检测是否处于屏幕共享状态
+ (NSDictionary *)checkScreenSharingStatus;

/// 执行一次屏幕共享检测任务
+ (NSDictionary *)checkScreenSharingStatusWithUserLocalScenario:(NSDictionary *_Nullable)userLocalScenario;

/// 检查设备当前是否处于通话状态 YES:处于通话状态 NO：没有处于通话状态
/// @param param 自定义参数，客户传递需要的参数,可以为空
+ (NSDictionary *)checkCallStatus:(NSString *_Nullable)param;

/// 检测当前设备是否是风险设备 YES:是风险设备 NO:不是风险设备
+ (BOOL)isRiskDevice;

+ (void)registerRiskDeviceCallback:(BCERiskDeviceCallback)callback;

/// 如需调用此函数，必须在调用初始化函数之前调用，用来判断是用标准版发送流程，还是使用安全设备不发送的流程，YES表示标准版流程，NO表示安全设备不发送的流程，默认是YES
/// @param b YES表示标准版流程，NO表示安全设备不发送的流程，默认是YES
+ (void)setStandardForNormalDevice:(BOOL)b;

/// 注册弹框策略回调接口（可选接口，用此接口以实现自定义弹框）
/// @param handler 弹框数据的回调block
+ (void)registerAlertActionHandler:(void (^)(BCEAlertContext * context))handler;

+ (void)checkOnDemandAgain;

@property (readwrite, nonatomic, copy) BCERiskURLSessionDidReceiveAuthenticationChallengeBlock _Nullable sessionDidReceiveAuthenticationChallenge;





////offline feature

/// 初始化离线探针接口（与下面的初始化接口二选一即可）
+ (void)initOfflineBangcleEveriskFromBundle;

/// 带有数据回调参数的离线探针初始化接口，使用此函数进行初始化就无需再调用注册离线数据回调接口
/// @param handler 数据回调的block
+ (void)initOfflineBangcleEveriskFromBundleWithDataCallback:(BCERiskEventHandler)handler;

/// 注册离线数据回调接口（可选接口）
/// @param handler 数据回调的block
+ (void)registerOfflineEventHandler:(BCERiskEventHandler)handler;

+ (void)addFilterStrings:(NSArray*)strings;

/// 获取威胁信息接口（可选接口）
+ (NSDictionary *_Nullable)getEnvInfo;

+ (void)changeABCEncrypt:(BOOL)isStandard;

////inner usage
+ (RiskStub *_Nullable)sharedManager;
@end

NS_ASSUME_NONNULL_END
