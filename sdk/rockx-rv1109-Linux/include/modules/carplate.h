/****************************************************************************
*
*    Copyright (c) 2017 - 2019 by Rockchip Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Rockchip Corporation. This is proprietary information owned by
*    Rockchip Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Rockchip Corporation.
*
*****************************************************************************/

#ifndef _ROCKX_CARPLATE_H
#define _ROCKX_CARPLATE_H

#include "../rockx_type.h"
#include "object_detection.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CarPlate Recognition Code Table
 *
 *     "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", \n
 *     "粤", "桂", "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", \n
 *     "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", \n
 *     "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", \n
 *     "港", "学", "使", "警", "澳", "挂", "军", "北", "南", "广", "沈", "兰", "成", "济", "海", "民", "航", "空" \n
*/
extern const char* const ROCKX_CARPLATE_RECOG_CODE[83];

/**
 * @brief CarPlate Recognition v3 Code Table
 *     "京", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑",
 *     "苏", "浙", "皖", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤",
 *     "桂", "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁",
 *     "新", "挂", "学", "警", "军", "应", "急", "民", "航", "港",
 *     "澳", "领", "使",
 *     "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
 *     "A", "B", "C", "D", "E", "F", "G", "H", "J", "K",
 *     "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V",
 *     "W", "X", "Y", "Z", "I", "O", "-"
 */
extern const char* const ROCKX_CARPLATE_RECOG_V3_CODE[80];

/**
 * @brief Car plate align Result (@ref rockx_carplate_align)
 */
typedef struct rockx_carplate_align_result_t {
    rockx_image_t aligned_image;        ///< Aligned car plate image
    float confidence;                   ///< Confidence
} rockx_carplate_align_result_t;

/**
 * @brief Car plate recognition Result (@ref rockx_carplate_recognize)
 */
typedef struct rockx_carplate_recog_result_t {
    int namecode[10];                   ///< Result code array (code table: @ref CARPLATE_RECOG_CODE)
    float scores[10];                   ///< Confidence for each result code
    int length;                         ///< Result array length
} rockx_carplate_recog_result_t;

/**
 * @brief Carplate Result (@ref rockx_carplate_recognize_all)
 */
typedef struct rockx_carplate_result_t {
    int id;
    rockx_rect_t box;
    rockx_image_t aligned_image;
    int str_codes[10];                   ///< Result code array (code table: @ref CARPLATE_RECOG_CODE)
    float str_scores[10];                   ///< Confidence for each result code
    int str_len;                         ///< Result array length
} rockx_carplate_result_t;

/**
 * @brief box and KeyPoints for carplate
 */
typedef struct rockx_carplate_det_t {
    int id;			   ///< carplate track id
    rockx_rect_t box;       ///< Object Region
    float score;		///< box score
    rockx_point_t points[4];   ///< key points
    rockx_image_t aligned_image;        ///< Aligned car plate image
} rockx_carplate_det_t;

/**
 * @brief KeyPoints Array
 */
typedef struct rockx_carplate_det_array_t {
	int count;							///< Array size
	rockx_carplate_det_t carplate[8];	///< Array of rockx_carplate_det_t
} rockx_carplate_det_array_t;

/**
 * Car Plate Detection
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_DETECTION module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param object_array [out] Car plate detection result
 * @param callback [in] Async callback function pointer
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_detect(rockx_handle_t handle, rockx_image_t *in_img, rockx_object_array_t *object_array,
                                  rockx_async_callback *callback);

/**
 * Car Plate Correction Alignment
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_ALIGN module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param detect_box [in] Carplat detection result box (get from @ref rockx_carplate_detect)
 * @param aligned_result [out] Aligned result (remember to release aligned_image via rockx_image_release())
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_align(rockx_handle_t handle, rockx_image_t *in_img, rockx_rect_t *detect_box,
                                 rockx_carplate_align_result_t *aligned_result);

/**
 * Car Plate Recognition
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_RECOG module(created by @ref rockx_create)
 * @param aligned_img [in] Aligned image of car plate (get from @ref rockx_carplate_align)
 * @param recog_result [out] Recognition result
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_recognize(rockx_handle_t handle, rockx_image_t *aligned_img,
                                rockx_carplate_recog_result_t *recog_result);


/**
 * Car Plate Recognition V3
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_RECOG module(created by @ref rockx_create)
 * @param aligned_img [in] Aligned image of car plate (get from @ref rockx_carplate_align)
 * @param recog_result [out] Recognition result
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_recognize_v3(rockx_handle_t handle, rockx_image_t* aligned_img, 
                                rockx_carplate_recog_result_t *recog_result);
/**
 * Carplate recognition for all detected car
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_RECOG_ALL module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param det_array [in] Detected Car
 * @param recog_results [out] Recognition result
 * @param recog_num [out] Recognition result number
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_recognize_all(rockx_handle_t handle, rockx_image_t *in_img, rockx_object_array_t *det_array,
                                rockx_carplate_result_t **recog_results, int *recog_num);

/**
 * Release carplate result
 *
 * @param recog_results [in] Recognition result to be release
 * @param recog_num [in] Recognition result number
 * @return rockx_ret_t
 */
rockx_ret_t rockx_carplate_result_release(rockx_carplate_result_t *recog_results, int recog_num);



/**
 * Car Plate Detection V2
 * @param handle [in] Handle of a created ROCKX_MODULE_CARPLATE_DETECTION module(created by @ref rockx_create)
 * @param in_img [in] Input image
 * @param object_array [out] Car plate detection result
 * @param callback [in] Async callback function pointer
 * @return @ref rockx_ret_t
 */
rockx_ret_t rockx_carplate_detect_v2(rockx_handle_t handle, rockx_image_t *in_img,
                                         rockx_carplate_det_array_t *carplate_array,
                                         rockx_async_callback *callback);

#ifdef __cplusplus
} //extern "C"
#endif

#endif // _ROCKX_CARPLATE_H