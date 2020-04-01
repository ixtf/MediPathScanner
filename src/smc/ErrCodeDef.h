#pragma once


/* ???? */
#define SMCE_NOERROR                                    0            /* ?? */

/*
*	????????
*/
#define SMCE_UNKNOWN                                    1            /*????*/
#define SMCE_ERR_PARAMETER                                2            /*????*/
#define SMCE_OPERATE_TIMEOUT                            3            /*????*/
#define SMCE_STATE_BUSY                                    4            /*???*/
#define SMCE_TOO_MANY_CONNECTS                            5            /*????*/
#define SMCE_ERR_INTERPOLATION                            6            /*????*/
#define SMCE_CONNECT_FAIL                                7            /*????*/
#define SMCE_CANNOT_CONNECT                                8            /*????*/
#define SMCE_INVALIAD_AXIS                                9            /*?????????*/
#define SMCE_ERR_TRANSPORT                                10            /*??????*/
#define SMCE_ERR_FIRMWARE_FILE                            12            /*??????*/
#define SMCE_NO_MATCH_FIRMWARE                            14            /*???????*/
#define SMCE_ERR_FIRMWARE_PARAMETER                        20            /*??????*/
#define SMCE_NO_OPERATE_FIRMWARE                        22            /*???????????*/
#define SMCE_ERR_UNSUPPORT                                24            /*??????*/
#define SMCE_ERR_PASSWORD                                25            /*????*/
#define SMCE_ERR_LIMITED_NUMBER_PASSWORD                26            /*????????*/
#define SMCE_ERR_AXIS_SEL_ERR                            30            /*??????????????*/
#define SMCE_ERR_HAND_AXIS_NUM_ERR                        31            /*??????????????*/
#define SMCE_ERR_AXIS_RATIO_ERR                            32            /*???????????????*/
#define SMCE_ERR_HANDWH_START                            33            /*?????????????????????*/
#define SMCE_ERR_AXIS_BUSY_STATE                        34            /*???????????????*/
#define SMCE_ERR_LIST_NUM_ERR                            50            /*LIST?????*/
#define SMCE_ERR_LIST_NOT_OEPN                            51            /*LIST?????*/
#define SMCE_ERR_PARA_NOT_VALID                            52            /*????????*/
#define SMCE_ERR_LIST_HAS_OPEN                            53            /*LIST????*/
#define SMCE_ERR_MAIN_LIST_NOT_OPEN                        54            /*LIST?????*/
#define SMCE_ERR_AXIS_NUM_ERR                            55            /*????????*/
#define SMCE_ERR_AXIS_MAP_ARRAY_ERR                        56            /*??????*/
#define SMCE_ERR_MAP_AXIS_ERR                            57            /*?????*/
#define SMCE_ERR_MAP_AXIS_BUSY                            58            /*????*/
#define SMCE_ERR_PARA_SET_FORBIT                        59            /*??????????*/
#define SMCE_ERR_FIFO_FULL                                60            /*?????*/
#define SMCE_ERR_RADIUS_ERR                                61            /*???0???????????*/
#define SMCE_ERR_MAINLIST_HAS_START                        62            /*LIST????*/
#define SMCE_ERR_ACC_TIME_ZERO                            63            /*??????0*/
#define SMCE_ERR_MAINLIST_NOT_START                        64            /*??LIST????*/
#define SMCE_ERR_POINT_SAME_ON_RADIUS                    67            /*???????????????????*/
#define SMCE_MCVP_SMOOTH_TIME_SET_ERROR                    80            /*s??????(????0)*/
#define SMCE_MCVP_START_VEL_SET_ERROR                    81            /*???????????(??0)*/
#define SMCE_MCVP_STEADY_VEL_SET_ERROR                    82            /*???????????(??? ?0)*/
#define SMCE_MCVP_END_VEL_SET_ERROR                        83            /*???????????(??0)*/
#define SMCE_MCVP_TOTAL_LENGTH_SET_ERROR                84            /*?????0?????*/
#define SMCE_ERR_AXIS_INDEX                                101            /*????????*/
#define SMCE_ERR_SET_WHILE_MOVING                        102            /*????????????*/
#define SMCE_ERR_ENTER_WHILE_MOVING                        103            /*?????????????*/
#define SMCE_ERR_PEL_STATE                                104            /*?????????????*/
#define SMCE_ERR_NEL_STATE                                105            /*?????????????*/
#define SMCE_ERR_SOFT_PEL_STATE                            106            /*??????????????*/
#define SMCE_ERR_SOFT_NEL_STATE                            107            /*??????????????*/
#define SMCE_ERR_FORCE_IN_OTHER_MODE                    108            /*???????????????*/
#define SMCE_ERR_MAX_VEL_ZERO                            109            /*????????????0*/
#define SMCE_ERR_EQU_ZERO                                110            /*???????????0*/
#define SMCE_ERR_BACKLASH_NEG                            111            /*??????????????*/
#define SMCE_ERR_MAX_PULSE                                112            /*??????????????*/
#define SMCE_ERR_CMP_EXCEED_MAX_AXISES                    121            /*?????????*/
#define SMCE_ERR_CMP_EXCEED_MAX_INDEX                    122            /*?????????????*/
#define SMCE_ERR_CMP_EXCEED_MAX_IO                        123            /*?????IO????*/
#define SMCE_ERR_CMP_EXCEED_MAX_CHAN                    124            /*???????IO????*/
#define SMCE_ERR_MAP_AXISIO_MAX_AXISES                    130            /*????????*/
#define SMCE_PVT_ERROR_AXISES_OVER_RANGE                140            /*???????*/
#define SMCE_PVT_ERROR_INDEX_OVER_RANGE                    141            /*????????????*/
#define SMCE_PVT_ERROR_INDEX_EXCEED                        142            /*????????????*/
#define SMCE_PVT_ERROR_TIME_EROOR                        143            /*??????0????*/
#define SMCE_HOME_ERROR_AXISES_OVER_RANGE                200            /*????????*/
#define SMCE_HOME_ERROR_MAX_VEL                            202            /*????????0*/
#define SMCE_HOME_ERROR_MAX_ACC                            203            /*??????????0*/
#define SMCE_HOME_ERROR_BOTH_LIMIT                        207            /*?????????, ?????? ??*/
#define SMCE_ERROR_ZSHELL_PARAERR                        1000        /*????*/
#define SMCE_ERROR_ZSHELL_STOP_USER                        1040        /*??????*/
#define SMCE_ERROR_ZSHELL_STOP_OTHERTASK                1041        /*????????*/
#define SMCE_ERROR_ZSHELL_PARA_CANNOT_MODIFIY            1042        /*????????, SET????*/
#define SMCE_ERROR_ZSHELL_ARRAY_OVER                    1043        /*????*/
#define SMCE_ERROR_ZSHELL_VAR_TOOMUCH                    1044        /*??????*/
#define SMCE_ERROR_ZSHELL_ARRAY_TOOMUCH                    1045        /*??????*/
#define SMCE_ERROR_ZSHELL_ARRAY_NOSPACE                    1046        /*??????*/
#define SMCE_ERROR_ZSHELL_SUB_TOOMUCH                    1047        /*SUB??*/
#define SMCE_ERROR_ZSHELL_LABEL_NAMEERR                    1048        /*??? ????*/
#define SMCE_ERROR_ZSHELL_LABEL_TOOMANYCHARES            1049        /*??? ????*/
#define SMCE_ERROR_ZSHELL_NO_RIGHTBRACKET                1050        /*?????*/
#define SMCE_ERROR_ZSHELL_UNKOWNCHAR                    1051        /*??????*/
#define SMCE_ERROR_ZSHELL_UNKOWN_LABEL                    1052        /*??????, ??????*/
#define SMCE_ERROR_ZSHELL_STOP_INVALIDCMD                1053        /*??????*/
#define SMCE_ERROR_ZSHELL_STOP_OVERSTACK                1054        /*??????*/
#define SMCE_ERROR_ZSHELL_OVER_RECURSION                1055        /*????*/
#define SMCE_ERROR_ZSHELL_NO_QUOTEEND                    1056        /*??????*/
#define SMCE_ERROR_ZSHELL_CMD_CANNOTREAD                1057        /*????, ?????????*/
#define SMCE_ERROR_ZSHELL_CMD_CANNOTRUN                    1058        /*???????????, ??? ??????*/
#define SMCE_ERROR_ZSHELL_LINE_MUST_END                    1059        /*?????, ????????*/
#define SMCE_ERROR_ZSHELL_ARRAY_NEEDINDEX                1060        /*??????? ?????*/
#define SMCE_ERROR_ZSHELL_NOTBRACKET_AFTERVAR            1061        /*????????*/
#define SMCE_ERROR_ZSHELL_DIM_CONFLICT                    1062        /*????????, ?????*/
#define SMCE_ERROR_ZSHELL_DIM_ARRAYLENGTHERR            1063        /*??????*/
#define SMCE_ERROR_ZSHELL_DIM_LABEL_SUB                    1064        /*??, ?? SUB*/
#define SMCE_ERROR_ZSHELL_DIM_LABEL_PARA                1065        /*??, ?? PARA*/
#define SMCE_ERROR_ZSHELL_DIM_LABEL_RESERVE                1066        /*??, ?? ??*/
#define SMCE_ERROR_ZSHELL_UNWANT_CHAR                    1067        /*???????*/
#define SMCE_ERROR_ZSHELL_STACK_NOPUSH                    1068        /*POP?????*/
#define SMCE_ERROR_ZSHELL_FORMAT_ERR                    1070        /*????*/
#define SMCE_ERROR_ZSHELL_SET_OVER                        1071        /*????, para(10) 10??*/
#define SMCE_ERROR_ZSHELL_PARA_RANGEERR                    1072        /*??????????????*/
#define SMCE_ERROR_ZSHELL_PARA_TOOMANY                    1073        /*?????????? ??*/
#define SMCE_ERROR_ZSHELL_PARA_TOOFEW                    1074        /*?????????? ??*/
#define SMCE_ERROR_ZSHELL_NO_EXPR                        1075        /*???????*/
#define SMCE_ERROR_ZSHELL_OPERNOPARA                    1076        /*???????*/
#define SMCE_ERROR_ZSHELL_NOPARA_BEFOREOPER                1077        /*?????????*/
#define SMCE_ERROR_ZSHELL_SIGNAL_CANNOTINEXPR            1078        /*???????????*/
#define SMCE_ERROR_ZSHELL_NEED_OPER                        1079        /*???????*/
#define SMCE_ERROR_ZSHELL_SUB_NOTSUB                    1080        /*CALL ???SUB*/
#define SMCE_ERROR_ZSHELL_NO_AUTO                        1081        /*??AUTO?????*/
#define SMCE_ERROR_ZSHELL_EQ_WANTED                        1082        /*????????, ?????? ????????*/
#define SMCE_ERROR_ZSHELL_FILE_VAIN                        1083        /*?????*/
#define SMCE_ERROR_ZSHELL_SUB_RENAME                    1084        /*SUB??, ??????????*/
#define SMCE_ERROR_ZSHELL_TASK_RUNNING                    1085        /*???????*/
#define SMCE_ERROR_ZSHELL_NEED_COMMA_BETWEEN_ PARA        1086        /*?????????*/
#define SMCE_ERROR_ZSHELL_NO_LEFTBRACKET                1087        /*?????*/
#define SMCE_ERROR_ZSHELL_TOOMANY_IFNESTED                1088        /*IF????*/
#define SMCE_ERROR_ZSHELL_TOOMANY_LOOPNESTED            1089        /*LOOP????*/
#define SMCE_ERROR_ZSHELL_MOVEAXISES_FEW                1090        /*?????*/
#define SMCE_ERROR_ZSHELL_CONST_VAR                        1091        /*??????*/
#define SMCE_ERROR_ZSHELL_NOT_ONLINECMD                    1092        /*????????*/
#define SMCE_ERROR_ZSHELL_AXIS_OVER                        1093        /*????*/
#define SMCE_ERROR_ZSHELL_CRD_OVER                        1094        /*?????*/
#define SMCE_ERROR_ZSHELL_STOP_UNKNOWN                    1099        /*????, ?????????? ??????*/
#define SMCE_ERROR_ZSHELL_DIVISION_BY_ZERO                1200        /*????????????? 0*/

/*
*	SDK?????
*/
#define SMCE_FAIL                                        -1            /* ???? */
#define SMCE_NOKEY                                        -2            /* ?????? */
#define SMCE_NOLISENCE                                    -3            /* ?????? */
#define SMCE_INVALID_PARAM                                -4            /* ???? */
#define SMCE_NOT_INIT                                    -5            /* ?????? */
#define SMCE_NOT_ENOUGH_MEM                                -6            /* ???? */

