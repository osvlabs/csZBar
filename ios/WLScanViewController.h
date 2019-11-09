//
//  WLScanViewController.h
//  Siemens Home
//
//  Created by Vitta on 2019/11/9.
//

#import <UIKit/UIKit.h>
#import <ZXingWrapper.h>
#import <LBXScanTypes.h>

@class LBXScanResult;

typedef NS_ENUM(NSInteger, SCANLIBRARYTYPE) {
    SLT_Native,
    SLT_ZXing,
    SLT_ZBar
};

// @[@"QRCode",@"BarCode93",@"BarCode128",@"BarCodeITF",@"EAN13"];
typedef NS_ENUM(NSInteger, SCANCODETYPE) {
    SCT_QRCode, //QR二维码
    SCT_BarCode93,
    SCT_BarCode128, //支付条形码(支付宝、微信支付条形码)
    SCT_BarCodeITF, //燃气回执联 条形码?
    SCT_BarEAN13    //一般用做商品码
};

/**
 扫码结果delegate,也可通过继承本控制器，override方法scanResultWithArray即可
 */
@protocol LBXScanViewControllerDelegate <NSObject>
@optional
- (void)scanResultWithArray:(NSArray<LBXScanResult *> *)array;
@end

@interface WLScanViewController : UIViewController <UIImagePickerControllerDelegate>
#pragma mark---- 需要初始化参数 ------
//当前选择的扫码库
@property(nonatomic, assign) SCANLIBRARYTYPE libraryType;

// 识别有效区域
@property(nonatomic, assign) CGRect cropRect;
//

/**
 当前选择的识别码制
 - ZXing暂不支持类型选择
 */
@property(nonatomic, assign) SCANCODETYPE scanCodeType;

//扫码结果委托，另外一种方案是通过继承本控制器，override方法scanResultWithArray即可
@property(nonatomic, weak) id<LBXScanViewControllerDelegate> delegate;

/**
 @brief 是否需要扫码图像
 */
@property(nonatomic, assign) BOOL isNeedScanImage;

/**
 @brief  启动区域识别功能，ZBar暂不支持
 */
@property(nonatomic, assign) BOOL isOpenInterestRect;

/**
 相机启动提示,如 相机启动中...
 */
@property(nonatomic, copy) NSString *cameraInvokeMsg;

#pragma mark-----  扫码使用的库对象 -------

#ifdef LBXScan_Define_Native
/**
 @brief  扫码功能封装对象
 */
@property(nonatomic, strong) LBXScanNative *scanObj;

#endif

#ifdef LBXScan_Define_ZXing
/**
 ZXing扫码对象
 */
@property(nonatomic, strong) ZXingWrapper *zxingObj;
#endif

#ifdef LBXScan_Define_ZBar
/**
 ZBar扫码对象
 */
@property(nonatomic, strong) LBXZBarWrapper *zbarObj;

#endif

#pragma mark - 扫码界面效果及提示等

/**
 @brief  扫码存储的当前图片
 */
@property(nonatomic, strong) UIImage *scanImage;

/**
 @brief  闪关灯开启状态记录
 */
@property(nonatomic, assign) BOOL isOpenFlash;

//打开相册
- (void)openLocalPhoto:(BOOL)allowsEditing;

//开关闪光灯
- (void)openOrCloseFlash;

//启动扫描
- (void)reStartDevice;

//关闭扫描
- (void)stopScan;

@end
