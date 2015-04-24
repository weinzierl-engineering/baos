//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS",	WITHOUT WARRANTY OF ANY KIND,	EXPRESS OR
// IMPLIED,	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE,	TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT,	TORT OR OTHERWISE,	ARISING FROM,	OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "pch/kdrive_pch.h"
#include "kdrive/knx/defines/DatapointTypes.h"

using namespace kdrive::knx;

#define COMPARE_DPT_TYPE(STR1, STR2, VAL) \
	if (STR1 == STR2) return VAL

int DatapointTypes::getTypeFromId(const std::string& datapointId)
{
	COMPARE_DPT_TYPE(datapointId,	"DPT-1",		DatapointType_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-1",		DatapointSubType_1_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-2",		DatapointSubType_1_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-3",		DatapointSubType_1_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-4",		DatapointSubType_1_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-5",		DatapointSubType_1_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-6",		DatapointSubType_1_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-7",		DatapointSubType_1_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-8",		DatapointSubType_1_8);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-9",		DatapointSubType_1_9);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-10",	DatapointSubType_1_10);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-11",	DatapointSubType_1_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-12",	DatapointSubType_1_12);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-15",	DatapointSubType_1_15);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-16",	DatapointSubType_1_16);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-17",	DatapointSubType_1_17);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-18",	DatapointSubType_1_18);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-19",	DatapointSubType_1_19);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-21",	DatapointSubType_1_21);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-22",	DatapointSubType_1_22);
	COMPARE_DPT_TYPE(datapointId,	"DPST-1-100",	DatapointSubtype_1_100);

	COMPARE_DPT_TYPE(datapointId,	"DPT-2",		DatapointType_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-1",		DatapointSubType_2_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-2",		DatapointSubType_2_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-3",		DatapointSubType_2_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-4",		DatapointSubType_2_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-5",		DatapointSubType_2_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-6",		DatapointSubType_2_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-7",		DatapointSubType_2_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-10",	DatapointSubType_2_10);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-11",	DatapointSubType_2_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-2-12",	DatapointSubType_2_12);

	COMPARE_DPT_TYPE(datapointId,	"DPT-3",		DatapointType_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-3-7",		DatapointSubType_3_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-3-8",		DatapointSubType_3_8);

	COMPARE_DPT_TYPE(datapointId,	"DPT-4",		DatapointType_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-4-1",		DatapointSubType_4_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-4-2",		DatapointSubType_4_2);

	COMPARE_DPT_TYPE(datapointId,	"DPT-5",		DatapointType_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-5-1",		DatapointSubType_5_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-5-3",		DatapointSubType_5_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-5-4",		DatapointSubType_5_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-5-10",	DatapointSubType_5_10);

	COMPARE_DPT_TYPE(datapointId,	"DPT-6",		DatapointType_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-6-1",		DatapointSubType_6_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-6-10",	DatapointSubType_6_10);

	COMPARE_DPT_TYPE(datapointId,	"DPT-7",		DatapointType_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-1",		DatapointSubType_7_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-2",		DatapointSubType_7_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-3",		DatapointSubType_7_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-4",		DatapointSubType_7_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-5",		DatapointSubType_7_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-6",		DatapointSubType_7_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-7-7",		DatapointSubType_7_7);

	COMPARE_DPT_TYPE(datapointId,	"DPT-8",		DatapointType_8);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-1",		DatapointSubType_8_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-2",		DatapointSubType_8_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-3",		DatapointSubType_8_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-4",		DatapointSubType_8_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-5",		DatapointSubType_8_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-6",		DatapointSubType_8_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-7",		DatapointSubType_8_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-8-10",	DatapointSubType_8_10);

	COMPARE_DPT_TYPE(datapointId,	"DPT-9",		DatapointType_9);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-1",		DatapointSubType_9_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-2",		DatapointSubType_9_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-3",		DatapointSubType_9_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-4",		DatapointSubType_9_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-5",		DatapointSubType_9_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-6",		DatapointSubType_9_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-7",		DatapointSubType_9_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-8",		DatapointSubType_9_8);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-10",	DatapointSubType_9_10);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-11",	DatapointSubType_9_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-20",	DatapointSubType_9_20);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-21",	DatapointSubType_9_21);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-22",	DatapointSubType_9_22);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-23",	DatapointSubType_9_23);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-24",	DatapointSubType_9_24);
	COMPARE_DPT_TYPE(datapointId,	"DPST-9-25",	DatapointSubType_9_25);

	COMPARE_DPT_TYPE(datapointId,	"DPT-10",		DatapointType_10);
	COMPARE_DPT_TYPE(datapointId,	"DPST-10-1",	DatapointSubType_10_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-11",		DatapointType_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-11-1",	DatapointSubType_11_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-12",		DatapointType_12);
	COMPARE_DPT_TYPE(datapointId,	"DPST-12-1",	DatapointSubType_12_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-13",		DatapointType_13);
	COMPARE_DPT_TYPE(datapointId,	"DPST-13-1",	DatapointSubType_13_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-13-100",	DatapointSubType_13_100);

	COMPARE_DPT_TYPE(datapointId,	"DPT-14",		DatapointType_14);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-0",	DatapointSubType_14_0);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-1",	DatapointSubType_14_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-2",	DatapointSubType_14_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-3",	DatapointSubType_14_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-4",	DatapointSubType_14_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-5",	DatapointSubType_14_5);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-6",	DatapointSubType_14_6);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-7",	DatapointSubType_14_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-8",	DatapointSubType_14_8);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-9",	DatapointSubType_14_9);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-10",	DatapointSubType_14_10);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-11",	DatapointSubType_14_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-12",	DatapointSubType_14_12);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-13",	DatapointSubType_14_13);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-14",	DatapointSubType_14_14);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-15",	DatapointSubType_14_15);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-16",	DatapointSubType_14_16);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-17",	DatapointSubType_14_17);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-18",	DatapointSubType_14_18);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-19",	DatapointSubType_14_19);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-20",	DatapointSubType_14_20);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-21",	DatapointSubType_14_21);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-22",	DatapointSubType_14_22);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-23",	DatapointSubType_14_23);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-24",	DatapointSubType_14_24);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-25",	DatapointSubType_14_25);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-26",	DatapointSubType_14_26);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-27",	DatapointSubType_14_27);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-28",	DatapointSubType_14_28);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-29",	DatapointSubType_14_29);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-30",	DatapointSubType_14_30);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-31",	DatapointSubType_14_31);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-32",	DatapointSubType_14_32);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-33",	DatapointSubType_14_33);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-34",	DatapointSubType_14_34);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-35",	DatapointSubType_14_35);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-36",	DatapointSubType_14_36);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-37",	DatapointSubType_14_37);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-38",	DatapointSubType_14_38);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-39",	DatapointSubType_14_39);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-40",	DatapointSubType_14_40);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-41",	DatapointSubType_14_41);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-42",	DatapointSubType_14_42);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-43",	DatapointSubType_14_43);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-44",	DatapointSubType_14_44);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-45",	DatapointSubType_14_45);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-46",	DatapointSubType_14_46);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-47",	DatapointSubType_14_47);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-48",	DatapointSubType_14_48);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-49",	DatapointSubType_14_49);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-50",	DatapointSubType_14_50);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-51",	DatapointSubType_14_51);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-52",	DatapointSubType_14_52);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-53",	DatapointSubType_14_53);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-54",	DatapointSubType_14_54);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-55",	DatapointSubType_14_55);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-56",	DatapointSubType_14_56);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-57",	DatapointSubType_14_57);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-58",	DatapointSubType_14_58);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-59",	DatapointSubType_14_59);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-60",	DatapointSubType_14_60);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-61",	DatapointSubType_14_61);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-62",	DatapointSubType_14_62);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-63",	DatapointSubType_14_63);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-64",	DatapointSubType_14_64);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-65",	DatapointSubType_14_65);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-66",	DatapointSubType_14_66);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-67",	DatapointSubType_14_67);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-68",	DatapointSubType_14_68);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-69",	DatapointSubType_14_69);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-70",	DatapointSubType_14_70);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-71",	DatapointSubType_14_71);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-72",	DatapointSubType_14_72);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-73",	DatapointSubType_14_73);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-74",	DatapointSubType_14_74);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-75",	DatapointSubType_14_75);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-76",	DatapointSubType_14_76);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-77",	DatapointSubType_14_77);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-78",	DatapointSubType_14_78);
	COMPARE_DPT_TYPE(datapointId,	"DPST-14-79",	DatapointSubType_14_79);

	COMPARE_DPT_TYPE(datapointId,	"DPT-15",		DatapointType_15);
	COMPARE_DPT_TYPE(datapointId,	"DPST-15-0",	DatapointSubType_15_0);

	COMPARE_DPT_TYPE(datapointId,	"DPT-16",		DatapointType_16);
	COMPARE_DPT_TYPE(datapointId,	"DPST-16-0",	DatapointSubType_16_0);
	COMPARE_DPT_TYPE(datapointId,	"DPST-16-1",	DatapointSubType_16_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-17",		DatapointType_17);
	COMPARE_DPT_TYPE(datapointId,	"DPST-17-1",	DatapointSubType_17_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-18",		DatapointType_18);
	COMPARE_DPT_TYPE(datapointId,	"DPST-18-1",	DatapointSubType_18_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-19",		DatapointType_19);
	COMPARE_DPT_TYPE(datapointId,	"DPST-19-1",	DatapointSubType_19_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-20",		DatapointType_20);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-1",	DatapointSubType_20_1);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-2",	DatapointSubType_20_2);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-3",	DatapointSubType_20_3);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-4",	DatapointSubType_20_4);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-7",	DatapointSubType_20_7);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-11",	DatapointSubType_20_11);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-12",	DatapointSubType_20_12);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-102",	DatapointSubType_20_102);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-103",	DatapointSubType_20_103);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-104",	DatapointSubType_20_104);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-105",	DatapointSubType_20_105);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-106",	DatapointSubType_20_106);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-107",	DatapointSubType_20_107);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-108",	DatapointSubType_20_108);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-109",	DatapointSubType_20_109);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-110",	DatapointSubType_20_110);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-111",	DatapointSubType_20_111);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-112",	DatapointSubType_20_112);
	COMPARE_DPT_TYPE(datapointId,	"DPST-20-113",	DatapointSubType_20_113);

	COMPARE_DPT_TYPE(datapointId,	"DPT-217",		DatapointType_217);
	COMPARE_DPT_TYPE(datapointId,	"DPST-217-1",	DatapointSubType_217_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-219",		DatapointType_219);
	COMPARE_DPT_TYPE(datapointId,	"DPST-219-1",	DatapointSubType_219_1);

	COMPARE_DPT_TYPE(datapointId,	"DPT-222",		DatapointType_222);
	COMPARE_DPT_TYPE(datapointId,	"DPST-222-100",	DatapointSubType_222_100);
	COMPARE_DPT_TYPE(datapointId,	"DPST-222-101",	DatapointSubType_222_101);

	return 0;
}
