#pragma once

#ifdef _WIN32

#include <windows.h>

#ifndef DEPRECATED
#define DEPRECATED	__declspec(deprecated)
#endif

#ifdef SMCENG_EXPORTS
#define SMCENG_API __declspec(dllexport)
#else
#define SMCENG_API __declspec(dllimport)
#endif

#else	// #ifdef _WIN32

#ifndef DEPRECATED
#define DEPRECATED
#endif

#include <stdint.h>

#define SMCENG_API

#endif    // #ifdef _WIN32

#include "ErrCodeDef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AXIS_X                0        /*X轴*/
#define AXIS_Y                1        /*Y轴*/
#define AXIS_Z                2        /*Z轴*/
#define AXIS_CNT                3        /*轴数量:x.y.z*/

//轴运动状态
#define MOTION_RUNNING            0   //轴运动中
#define MOTION_STOP                1   //轴运动停止

typedef enum enCapMode {
    SMC_CAP_SINGLE = 0,            /*运动停下等待拍照完成*/
    SMC_CAP_CONTINUE = 1,            /*运动时连续拍照*/
} SMCCapMode;

typedef void *SMCEngContext;            /* 引擎实例上下文 */

/* 初始化参数 */
typedef struct {
    const char *smcip;                        /* 控制器IP，默认设置为："192.168.5.11" */

    /*控制器参数*/
    double dLimitposition[AXIS_CNT];            /*工作台限程，最大行程 */
    double dPulsePerRotation[AXIS_CNT];            /*脉冲数/转，电机每转一周的脉冲数*/
    double dOriginalDrift[AXIS_CNT];            /*零点偏移，单位：脉冲数*/
    double dAccTime[AXIS_CNT];                    /*加速时间，单位：秒*/
    double dDecTime[AXIS_CNT];                    /*减速时间，单位：秒*/
    double dSTime[AXIS_CNT];                    /*S段时间，单位：秒*/
    double dRunVelocity[AXIS_CNT];                /*自动运行速度，单位：脉冲数/秒*/
    double dStartVelocity[AXIS_CNT];            /*起始速度 单位：脉冲数/秒*/
    double dStopVelocity[AXIS_CNT];                /*停止速度 单位：脉冲数/秒*/
    double dHomeLowVelocity[AXIS_CNT];            /*回原点低速度 单位：脉冲数/秒*/
    double dHomeHighVelocity[AXIS_CNT];            /*回原点高速度，单位：脉冲数/秒*/
    double dBeginParking[AXIS_CNT];                /*开始泊车位，单位：脉冲数*/
    double dEndParking[AXIS_CNT];                /*停止泊车位，单位：脉冲数*/
    double dSCrewPitch[AXIS_CNT];                /*丝杠螺距*/
    double dManualVelocity[AXIS_CNT];            /*手动运行速度，单位：脉冲数/秒*/

    int blockMode;                            /* 是否阻塞处理模式(0－非阻塞，1－阻塞),默认为阻塞模式 */

} SMCEngInitParam;

typedef struct {
    unsigned short major;
    unsigned short minor;
    unsigned int patch;
    char version[64];

} SMCEngVersionInfo;

/*
*	初始化引擎
*		param[in]	- 初始化参数,如param==NULL，则采用系统默认参数
*		cxt[out]		- 成功返回引擎上下文，使用完必须用SMCEng_Uninit()释放
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_Init(SMCEngInitParam *param, SMCEngContext *cxt);

/*
*	释放引擎上下文
*/
SMCENG_API void SMCEng_Uninit(SMCEngContext cxt);

/*
*	获取系统默认参数
*/
SMCENG_API void SMCEng_GetDefaultParameter(SMCEngInitParam *param);

/*
*	指定轴复位
*		cxt[in]		- 引擎上下文
*		axis[in]		- 指定轴号：AXIS_X、AXIS_Y或AXIS_Z，所有轴设为为255；
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_Reset(SMCEngContext cxt, int axis);

/*
*	指定轴运动状态
*		cxt[in]		- 引擎上下文
*		axis[in]	- 指定轴号：AXIS_X、AXIS_Y或AXIS_Z；
*	返回值
*		轴运动状态: 1--停止状态；0--运动状态。
*/
SMCENG_API int SMCEng_CheckDone(SMCEngContext cxt, int axis);

/*
*	移到指定泊车位
*		cxt[in]		- 引擎上下文
*		parking[in]	- 指定泊车位：0--开始泊车位，1--停止泊车位；
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_MoveToParking(SMCEngContext cxt, int parking);

/*
*	获取指定轴当前位置
*		cxt[in]			- 引擎上下文
*		axis[in]			- 指定轴号：AXIS_X、AXIS_Y或AXIS_Z；
*		position[out]	- 指定轴当前位置，脉冲数；
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_GetCurrentPosition(SMCEngContext cxt, int axis, double *position);

/*
*	指定轴移到指定位置
*		cxt[in]		- 引擎上下文
*		axis[in]		- 指定轴号：AXIS_X、AXIS_Y或AXIS_Z；
*		begin[in]	- 开始位置，脉冲数
*		end[in]		- 结束位置，脉冲数
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_MoveTo(SMCEngContext cxt, int axis, double begin, double end);

/*
*	指定轴行扫描
*		cxt[in]			- 引擎上下文
*		axis[in]			- 指定轴号：AXIS_X、AXIS_Y或AXIS_Z；
*		begin[in]		- 开始位置，脉冲数
*		end[in]			- 结束位置，脉冲数
*		step[in]			- 步进距离，脉冲数
*		bCapture[in]		- 是否启动相机硬触发拍照
*		capMode[in]		- 运动拍照模式
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_ScanLine(SMCEngContext cxt, int axis, double begin, double end, double step,
                               bool bCapture, SMCCapMode capMode);


/*
*	全轴块扫描
*		cxt[in]			- 引擎上下文
*		begin_x[in]		- X轴开始位置，脉冲数
*		end_x[in]		- X轴结束位置，脉冲数
*		step_x[in]		- X轴步进距离，脉冲数
*		begin_y[in]		- Y轴开始位置，脉冲数
*		end_y[in]		- Y轴结束位置，脉冲数
*		step_y[in]		- Y轴步进距离，脉冲数
*		pos_z[in]		- Z轴位置，脉冲数
*		bCapture[in]		- 是否启动相机硬触发拍照
*		capByAxis[in]	- 拍照参考轴,AXIS_X or AXIS_Y
*		capMode[in]		- 运动拍照模式
*	返回值
*		错误代码，ErrCodeDef.h定义
*/
SMCENG_API int SMCEng_ScanBlock(SMCEngContext cxt, double begin_x, double end_x, double step_x,
                                double begin_y, double end_y, double step_y, double pos_z, bool bCapture, int capByAxis,
                                SMCCapMode capMode);

/*
*	获得控制器发布版本号
*		version[out] - 控制器发布版本信息
*   返回值
*		成功返回0，否则返回错误码
*/
SMCENG_API int SMCEng_GetHWCardVersion(SMCEngContext cxt, char *version);

/*
*	获得SDK版本号
*		info[out] - SDK版本信息
*   返回值
*		成功返回0，否则返回错误码
*/
SMCENG_API int SMCEng_GetSDKVersion(SMCEngVersionInfo *info);

#ifdef __cplusplus
}
#endif
