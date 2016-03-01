//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "pch/kdrive_pch.h"
#include "kdrive/knx/datapoint/DatapointFactory.h"
#include "kdrive/knx/defines/DatapointTypes.h"
#include <Poco/Exception.h>

using namespace kdrive::knx;
using Poco::Exception;

Datapoint DatapointFactory::create(int datapointType)
{
	switch (datapointType)
	{
		case DatapointTypes::DatapointType_1:
			return Datapoint("DPT-1", "1", "1.xxx", "1-bit", "1");
		case DatapointTypes::DatapointSubType_1_1:
			return Datapoint("DPST-1-1", "1", "DPT_Switch", "switch", "1");
		case DatapointTypes::DatapointSubType_1_2:
			return Datapoint("DPST-1-2", "2", "DPT_Bool", "boolean", "1");
		case DatapointTypes::DatapointSubType_1_3:
			return Datapoint("DPST-1-3", "3", "DPT_Enable", "enable", "1");
		case DatapointTypes::DatapointSubType_1_4:
			return Datapoint("DPST-1-4", "4", "DPT_Ramp", "ramp", "1");
		case DatapointTypes::DatapointSubType_1_5:
			return Datapoint("DPST-1-5", "5", "DPT_Alarm", "alarm", "1");
		case DatapointTypes::DatapointSubType_1_6:
			return Datapoint("DPST-1-6", "6", "DPT_BinaryValue", "binary value", "1");
		case DatapointTypes::DatapointSubType_1_7:
			return Datapoint("DPST-1-7", "7", "DPT_Step", "step", "1");
		case DatapointTypes::DatapointSubType_1_8:
			return Datapoint("DPST-1-8", "8", "DPT_UpDown", "up/down", "1");
		case DatapointTypes::DatapointSubType_1_9:
			return Datapoint("DPST-1-9", "9", "DPT_OpenClose", "open/close", "1");
		case DatapointTypes::DatapointSubType_1_10:
			return Datapoint("DPST-1-10", "10", "DPT_Start", "start/stop", "1");
		case DatapointTypes::DatapointSubType_1_11:
			return Datapoint("DPST-1-11", "11", "DPT_State", "state", "1");
		case DatapointTypes::DatapointSubType_1_12:
			return Datapoint("DPST-1-12", "12", "DPT_Invert", "invert", "1");
		case DatapointTypes::DatapointSubType_1_13:
			return Datapoint("DPST-1-13", "13", "DPT_DimSendStyle", "dim send style", "1");
		case DatapointTypes::DatapointSubType_1_14:
			return Datapoint("DPST-1-14", "14", "DPT_InputSource", "input source", "1");
		case DatapointTypes::DatapointSubType_1_15:
			return Datapoint("DPST-1-15", "15", "DPT_Reset", "reset", "1");
		case DatapointTypes::DatapointSubType_1_16:
			return Datapoint("DPST-1-16", "16", "DPT_Ack", "acknowledge", "1");
		case DatapointTypes::DatapointSubType_1_17:
			return Datapoint("DPST-1-17", "17", "DPT_Trigger", "trigger", "1");
		case DatapointTypes::DatapointSubType_1_18:
			return Datapoint("DPST-1-18", "18", "DPT_Occupancy", "occupancy", "1");
		case DatapointTypes::DatapointSubType_1_19:
			return Datapoint("DPST-1-19", "19", "DPT_Window_Door", "window/door", "1");
		case DatapointTypes::DatapointSubType_1_21:
			return Datapoint("DPST-1-21", "21", "DPT_LogicalFunction", "logical function", "1");
		case DatapointTypes::DatapointSubType_1_22:
			return Datapoint("DPST-1-22", "22", "DPT_Scene_AB", "scene", "1");
		case DatapointTypes::DatapointSubType_1_23:
			return Datapoint("DPST-1-23", "23", "DPT_ShutterBlinds_Mode", "schutter/blinds mode", "1");
		case DatapointTypes::DatapointSubType_1_100:
			return Datapoint("DPST-1-100", "100", "DPT_Heat_Cool", "cooling/heating", "1");

		case DatapointTypes::DatapointType_2:
			return Datapoint("DPT-2", "2", "2.xxx", "1-bit controlled", "2");
		case DatapointTypes::DatapointSubType_2_1:
			return Datapoint("DPST-2-1", "1", "DPT_Switch_Control", "switch control", "2");
		case DatapointTypes::DatapointSubType_2_2:
			return Datapoint("DPST-2-2", "2", "DPT_Bool_Control", "boolean control", "2");
		case DatapointTypes::DatapointSubType_2_3:
			return Datapoint("DPST-2-3", "3", "DPT_Enable_Control", "enable control", "2");
		case DatapointTypes::DatapointSubType_2_4:
			return Datapoint("DPST-2-4", "4", "DPT_Ramp_Control", "ramp control", "2");
		case DatapointTypes::DatapointSubType_2_5:
			return Datapoint("DPST-2-5", "5", "DPT_Alarm_Control", "alarm control", "2");
		case DatapointTypes::DatapointSubType_2_6:
			return Datapoint("DPST-2-6", "6", "DPT_BinaryValue_Control", "binary value control", "2");
		case DatapointTypes::DatapointSubType_2_7:
			return Datapoint("DPST-2-7", "7", "DPT_Step_Control", "step control", "2");
		case DatapointTypes::DatapointSubType_2_8:
			return Datapoint("DPST-2-8", "8", "DPT_Direction1_Control", "direction control 1", "2");
		case DatapointTypes::DatapointSubType_2_9:
			return Datapoint("DPST-2-9", "9", "DPT_Direction2_Control", "direction control 2", "2");
		case DatapointTypes::DatapointSubType_2_10:
			return Datapoint("DPST-2-10", "10", "DPT_Start_Control", "start control", "2");
		case DatapointTypes::DatapointSubType_2_11:
			return Datapoint("DPST-2-11", "11", "DPT_State_Control", "state control", "2");
		case DatapointTypes::DatapointSubType_2_12:
			return Datapoint("DPST-2-12", "12", "DPT_Invert_Control", "invert control", "2");

		case DatapointTypes::DatapointType_3:
			return Datapoint("DPT-3", "3", "3.xxx", "3-bit controlled", "4");
		case DatapointTypes::DatapointSubType_3_7:
			return Datapoint("DPST-3-7", "7", "DPT_Control_Dimming", "dimming control", "4");
		case DatapointTypes::DatapointSubType_3_8:
			return Datapoint("DPST-3-8", "8", "DPT_Control_Blinds", "blind control", "4");

		case DatapointTypes::DatapointType_4:
			return Datapoint("DPT-4", "4", "4.xxx", "character", "8");
		case DatapointTypes::DatapointSubType_4_1:
			return Datapoint("DPST-4-1", "1", "DPT_Char_ASCII", "character (ASCII)", "8");
		case DatapointTypes::DatapointSubType_4_2:
			return Datapoint("DPST-4-2", "2", "DPT_Char_8859_1", "character (ISO 8859-1)", "8");

		case DatapointTypes::DatapointType_5:
			return Datapoint("DPT-5", "5", "5.xxx", "8-bit unsigned value", "8");
		case DatapointTypes::DatapointSubType_5_1:
			return Datapoint("DPST-5-1", "1", "DPT_Scaling", "percentage (0..100%)", "8");
		case DatapointTypes::DatapointSubType_5_3:
			return Datapoint("DPST-5-3", "3", "DPT_Angle", "angle (degrees)", "8");
		case DatapointTypes::DatapointSubType_5_4:
			return Datapoint("DPST-5-4", "4", "DPT_Percent_U8", "percentage (0..255%)", "8");
		case DatapointTypes::DatapointSubType_5_5:
			return Datapoint("DPST-5-5", "5", "DPT_DecimalFactor", "ratio (0..255)", "8");
		case DatapointTypes::DatapointSubType_5_6:
			return Datapoint("DPST-5-6", "6", "DPT_Tariff", "tariff (0..255)", "8");
		case DatapointTypes::DatapointSubType_5_10:
			return Datapoint("DPST-5-10", "10", "DPT_Value_1_Ucount", "counter pulses (0..255)", "8");

		case DatapointTypes::DatapointType_6:
			return Datapoint("DPT-6", "6", "6.xxx", "8-bit signed value", "8");
		case DatapointTypes::DatapointSubType_6_1:
			return Datapoint("DPST-6-1", "1", "DPT_Percent_V8", "percentage (-128..127%)", "8");
		case DatapointTypes::DatapointSubType_6_10:
			return Datapoint("DPST-6-10", "10", "DPT_Value_1_Count", "counter pulses (-128..127)", "8");
		case DatapointTypes::DatapointSubType_6_20:
			return Datapoint("DPST-6-20", "20", "DPT_Status_Mode3", "status with mode", "8");

		case DatapointTypes::DatapointType_7:
			return Datapoint("DPT-7", "7", "7.xxx", "2-byte unsigned value", "16");
		case DatapointTypes::DatapointSubType_7_1:
			return Datapoint("DPST-7-1", "1", "DPT_Value_2_Ucount", "pulses", "16");
		case DatapointTypes::DatapointSubType_7_2:
			return Datapoint("DPST-7-2", "2", "DPT_TimePeriodMsec", "time (ms)", "16");
		case DatapointTypes::DatapointSubType_7_3:
			return Datapoint("DPST-7-3", "3", "DPT_TimePeriod10Msec", "time (10 ms)", "16");
		case DatapointTypes::DatapointSubType_7_4:
			return Datapoint("DPST-7-4", "4", "DPT_TimePeriod100Msec", "time (100 ms)", "16");
		case DatapointTypes::DatapointSubType_7_5:
			return Datapoint("DPST-7-5", "5", "DPT_TimePeriodSec", "time (s)", "16");
		case DatapointTypes::DatapointSubType_7_6:
			return Datapoint("DPST-7-6", "6", "DPT_TimePeriodMin", "time (min)", "16");
		case DatapointTypes::DatapointSubType_7_7:
			return Datapoint("DPST-7-7", "7", "DPT_TimePeriodHrs", "time (h)", "16");
		case DatapointTypes::DatapointSubType_7_10:
			return Datapoint("DPST-7-10", "10", "DPT_PropDataType", "property data type", "16");
		case DatapointTypes::DatapointSubType_7_11:
			return Datapoint("DPST-7-11", "11", "DPT_Length_mm", "length (mm)", "16");
		case DatapointTypes::DatapointSubType_7_12:
			return Datapoint("DPST-7-12", "12", "DPT_UElCurrentmA", "current (mA)", "16");
		case DatapointTypes::DatapointSubType_7_13:
			return Datapoint("DPST-7-13", "13", "DPT_Brightness", "brightness (lux)", "16");

		case DatapointTypes::DatapointType_8:
			return Datapoint("DPT-8", "8", "8.xxx", "2-byte signed value", "16");
		case DatapointTypes::DatapointSubType_8_1:
			return Datapoint("DPST-8-1", "1", "DPT_Value_2_Count", "pulses difference", "16");
		case DatapointTypes::DatapointSubType_8_2:
			return Datapoint("DPST-8-2", "2", "DPT_DeltaTimeMsec", "time lag (ms)", "16");
		case DatapointTypes::DatapointSubType_8_3:
			return Datapoint("DPST-8-3", "3", "DPT_DeltaTime10Msec", "time lag(10 ms)", "16");
		case DatapointTypes::DatapointSubType_8_4:
			return Datapoint("DPST-8-4", "4", "DPT_DeltaTime100Msec", "time lag (100 ms)", "16");
		case DatapointTypes::DatapointSubType_8_5:
			return Datapoint("DPST-8-5", "5", "DPT_DeltaTimeSec", "time lag (s)", "16");
		case DatapointTypes::DatapointSubType_8_6:
			return Datapoint("DPST-8-6", "6", "DPT_DeltaTimeMin", "time lag (min)", "16");
		case DatapointTypes::DatapointSubType_8_7:
			return Datapoint("DPST-8-7", "7", "DPT_DeltaTimeHrs", "time lag (h)", "16");
		case DatapointTypes::DatapointSubType_8_10:
			return Datapoint("DPST-8-10", "10", "DPT_Percent_V16", "percentage difference (%)", "16");
		case DatapointTypes::DatapointSubType_8_11:
			return Datapoint("DPST-8-11", "11", "DPT_Rotation_Angle", "rotation angle ()", "16");

		case DatapointTypes::DatapointType_9:
			return Datapoint("DPT-9", "9", "9.xxx", "2-byte float value", "16");
		case DatapointTypes::DatapointSubType_9_1:
			return Datapoint("DPST-9-1", "1", "DPT_Value_Temp", "temperature (C)", "16");
		case DatapointTypes::DatapointSubType_9_2:
			return Datapoint("DPST-9-2", "2", "DPT_Value_Tempd", "temperature difference (K)", "16");
		case DatapointTypes::DatapointSubType_9_3:
			return Datapoint("DPST-9-3", "3", "DPT_Value_Tempa", "kelvin/hour (K/h)", "16");
		case DatapointTypes::DatapointSubType_9_4:
			return Datapoint("DPST-9-4", "4", "DPT_Value_Lux", "lux (Lux)", "16");
		case DatapointTypes::DatapointSubType_9_5:
			return Datapoint("DPST-9-5", "5", "DPT_Value_Wsp", "speed (m/s)", "16");
		case DatapointTypes::DatapointSubType_9_6:
			return Datapoint("DPST-9-6", "6", "DPT_Value_Pres", "pressure (Pa)", "16");
		case DatapointTypes::DatapointSubType_9_7:
			return Datapoint("DPST-9-7", "7", "DPT_Value_Humidity", "humidity (%)", "16");
		case DatapointTypes::DatapointSubType_9_8:
			return Datapoint("DPST-9-8", "8", "DPT_Value_AirQuality", "parts/million (ppm)", "16");
		case DatapointTypes::DatapointSubType_9_9:
			return Datapoint("DPST-9-9", "9", "DPT_Value_AirFlow", "air flow (m/h)", "16");
		case DatapointTypes::DatapointSubType_9_10:
			return Datapoint("DPST-9-10", "10", "DPT_Value_Time1", "time (s)", "16");
		case DatapointTypes::DatapointSubType_9_11:
			return Datapoint("DPST-9-11", "11", "DPT_Value_Time2", "time (ms)", "16");
		case DatapointTypes::DatapointSubType_9_20:
			return Datapoint("DPST-9-20", "20", "DPT_Value_Volt", "voltage (mV)", "16");
		case DatapointTypes::DatapointSubType_9_21:
			return Datapoint("DPST-9-21", "21", "DPT_Value_Curr", "current (mA)", "16");
		case DatapointTypes::DatapointSubType_9_22:
			return Datapoint("DPST-9-22", "22", "DPT_PowerDensity", "power denisity (W/m)", "16");
		case DatapointTypes::DatapointSubType_9_23:
			return Datapoint("DPST-9-23", "23", "DPT_KelvinPerPercent", "kelvin/percent (K/%)", "16");
		case DatapointTypes::DatapointSubType_9_24:
			return Datapoint("DPST-9-24", "24", "DPT_Power", "power (kW)", "16");
		case DatapointTypes::DatapointSubType_9_25:
			return Datapoint("DPST-9-25", "25", "DPT_Value_Volume_Flow", "volume flow (l/h)", "16");
		case DatapointTypes::DatapointSubType_9_26:
			return Datapoint("DPST-9-26", "26", "DPT_Rain_Amount", "rain amount (l/m)", "16");
		case DatapointTypes::DatapointSubType_9_27:
			return Datapoint("DPST-9-27", "27", "DPT_Value_Temp_F", "temperature (F)", "16");
		case DatapointTypes::DatapointSubType_9_28:
			return Datapoint("DPST-9-28", "28", "DPT_Value_Wsp_kmh", "wind speed (km/h)", "16");

		case DatapointTypes::DatapointType_10:
			return Datapoint("DPT-10", "10", "10.xxx", "time", "24");
		case DatapointTypes::DatapointSubType_10_1:
			return Datapoint("DPST-10-1", "1", "DPT_TimeOfDay", "time of day", "24");

		case DatapointTypes::DatapointType_11:
			return Datapoint("DPT-11", "11", "11.xxx", "date", "24");
		case DatapointTypes::DatapointSubType_11_1:
			return Datapoint("DPST-11-1", "1", "DPT_Date", "date", "24");

		case DatapointTypes::DatapointType_12:
			return Datapoint("DPT-12", "12", "12.xxx", "4-byte unsigned value", "32");
		case DatapointTypes::DatapointSubType_12_1:
			return Datapoint("DPST-12-1", "1", "DPT_Value_4_Ucount", "counter pulses (unsigned)", "32");

		case DatapointTypes::DatapointType_13:
			return Datapoint("DPT-13", "13", "13.xxx", "4-byte signed value", "32");
		case DatapointTypes::DatapointSubType_13_1:
			return Datapoint("DPST-13-1", "1", "DPT_Value_4_Count", "counter pulses (signed)", "32");
		case DatapointTypes::DatapointSubType_13_2:
			return Datapoint("DPST-13-2", "2", "DPT_FlowRate_m3/h", "flow rate (m/h)", "32");
		case DatapointTypes::DatapointSubType_13_10:
			return Datapoint("DPST-13-10", "10", "DPT_ActiveEnergy", "active energy (Wh)", "32");
		case DatapointTypes::DatapointSubType_13_11:
			return Datapoint("DPST-13-11", "11", "DPT_ApparantEnergy", "apparant energy (VAh)", "32");
		case DatapointTypes::DatapointSubType_13_12:
			return Datapoint("DPST-13-12", "12", "DPT_ReactiveEnergy", "reactive energy (VARh)", "32");
		case DatapointTypes::DatapointSubType_13_13:
			return Datapoint("DPST-13-13", "13", "DPT_ActiveEnergy_kWh", "active energy (kWh)", "32");
		case DatapointTypes::DatapointSubType_13_14:
			return Datapoint("DPST-13-14", "14", "DPT_ApparantEnergy_kVAh", "apparant energy (kVAh)", "32");
		case DatapointTypes::DatapointSubType_13_15:
			return Datapoint("DPST-13-15", "15", "DPT_ReactiveEnergy_kVARh", "reactive energy (kVARh)", "32");
		case DatapointTypes::DatapointSubType_13_100:
			return Datapoint("DPST-13-100", "100", "DPT_LongDeltaTimeSec", "time lag (s)", "32");

		case DatapointTypes::DatapointType_14:
			return Datapoint("DPT-14", "14", "14.xxx", "4-byte float value", "32");
		case DatapointTypes::DatapointSubType_14_0:
			return Datapoint("DPST-14-0", "0", "DPT_Value_Acceleration", "acceleration (m/s)", "32");
		case DatapointTypes::DatapointSubType_14_1:
			return Datapoint("DPST-14-1", "1", "DPT_Value_Acceleration_Angular", "angular acceleration (rad/s)", "32");
		case DatapointTypes::DatapointSubType_14_2:
			return Datapoint("DPST-14-2", "2", "DPT_Value_Activation_Energy", "activation energy (J/mol)", "32");
		case DatapointTypes::DatapointSubType_14_3:
			return Datapoint("DPST-14-3", "3", "DPT_Value_Activity", "radioactive activity (1/s)", "32");
		case DatapointTypes::DatapointSubType_14_4:
			return Datapoint("DPST-14-4", "4", "DPT_Value_Mol", "amount of substance (mol)", "32");
		case DatapointTypes::DatapointSubType_14_5:
			return Datapoint("DPST-14-5", "5", "DPT_Value_Amplitude", "amplitude", "32");
		case DatapointTypes::DatapointSubType_14_6:
			return Datapoint("DPST-14-6", "6", "DPT_Value_AngleRad", "angle (radiant)", "32");
		case DatapointTypes::DatapointSubType_14_7:
			return Datapoint("DPST-14-7", "7", "DPT_Value_AngleDeg", "angle (degree)", "32");
		case DatapointTypes::DatapointSubType_14_8:
			return Datapoint("DPST-14-8", "8", "DPT_Value_Angular_Momentum", "angular momentum (Js)", "32");
		case DatapointTypes::DatapointSubType_14_9:
			return Datapoint("DPST-14-9", "9", "DPT_Value_Angular_Velocity", "angular velocity (rad/s)", "32");
		case DatapointTypes::DatapointSubType_14_10:
			return Datapoint("DPST-14-10", "10", "DPT_Value_Area", "area (m*m)", "32");
		case DatapointTypes::DatapointSubType_14_11:
			return Datapoint("DPST-14-11", "11", "DPT_Value_Capacitance", "capacitance (F)", "32");
		case DatapointTypes::DatapointSubType_14_12:
			return Datapoint("DPST-14-12", "12", "DPT_Value_Charge_DensitySurface", "flux density (C/m)", "32");
		case DatapointTypes::DatapointSubType_14_13:
			return Datapoint("DPST-14-13", "13", "DPT_Value_Charge_DensityVolume", "charge density (C/m)", "32");
		case DatapointTypes::DatapointSubType_14_14:
			return Datapoint("DPST-14-14", "14", "DPT_Value_Compressibility", "compressibility (m/N)", "32");
		case DatapointTypes::DatapointSubType_14_15:
			return Datapoint("DPST-14-15", "15", "DPT_Value_Conductance", "conductance (S)", "32");
		case DatapointTypes::DatapointSubType_14_16:
			return Datapoint("DPST-14-16", "16", "DPT_Value_Electrical_Conductivity", "conductivity  (S/m)", "32");
		case DatapointTypes::DatapointSubType_14_17:
			return Datapoint("DPST-14-17", "17", "DPT_Value_Density", "density (kg/m)", "32");
		case DatapointTypes::DatapointSubType_14_18:
			return Datapoint("DPST-14-18", "18", "DPT_Value_Electric_Charge", "electric charge (C)", "32");
		case DatapointTypes::DatapointSubType_14_19:
			return Datapoint("DPST-14-19", "19", "DPT_Value_Electric_Current", "electric current (A)", "32");
		case DatapointTypes::DatapointSubType_14_20:
			return Datapoint("DPST-14-20", "20", "DPT_Value_Electric_CurrentDensity", "electric current density (A/m)", "32");
		case DatapointTypes::DatapointSubType_14_21:
			return Datapoint("DPST-14-21", "21", "DPT_Value_Electric_DipoleMoment", "electric dipole moment (Cm)", "32");
		case DatapointTypes::DatapointSubType_14_22:
			return Datapoint("DPST-14-22", "22", "DPT_Value_Electric_Displacement", "electric displacement (C/m)", "32");
		case DatapointTypes::DatapointSubType_14_23:
			return Datapoint("DPST-14-23", "23", "DPT_Value_Electric_FieldStrength", "electric field strength (V/m)", "32");
		case DatapointTypes::DatapointSubType_14_24:
			return Datapoint("DPST-14-24", "24", "DPT_Value_Electric_Flux", "electric flux (C)", "32");
		case DatapointTypes::DatapointSubType_14_25:
			return Datapoint("DPST-14-25", "25", "DPT_Value_Electric_FluxDensity", "electric flux density (C/m)", "32");
		case DatapointTypes::DatapointSubType_14_26:
			return Datapoint("DPST-14-26", "26", "DPT_Value_Electric_Polarization", "electric polarization (C/m)", "32");
		case DatapointTypes::DatapointSubType_14_27:
			return Datapoint("DPST-14-27", "27", "DPT_Value_Electric_Potential", "electric potential (V)", "32");
		case DatapointTypes::DatapointSubType_14_28:
			return Datapoint("DPST-14-28", "28", "DPT_Value_Electric_PotentialDifference", "electric potential difference (V)", "32");
		case DatapointTypes::DatapointSubType_14_29:
			return Datapoint("DPST-14-29", "29", "DPT_Value_ElectromagneticMoment", "electromagnetic moment (Am)", "32");
		case DatapointTypes::DatapointSubType_14_30:
			return Datapoint("DPST-14-30", "30", "DPT_Value_Electromotive_Force", "electromotive force (V)", "32");
		case DatapointTypes::DatapointSubType_14_31:
			return Datapoint("DPST-14-31", "31", "DPT_Value_Energy", "energy (J)", "32");
		case DatapointTypes::DatapointSubType_14_32:
			return Datapoint("DPST-14-32", "32", "DPT_Value_Force", "force (N)", "32");
		case DatapointTypes::DatapointSubType_14_33:
			return Datapoint("DPST-14-33", "33", "DPT_Value_Frequency", "frequency (Hz)", "32");
		case DatapointTypes::DatapointSubType_14_34:
			return Datapoint("DPST-14-34", "34", "DPT_Value_Angular_Frequency", "angular frequency (rad/s)", "32");
		case DatapointTypes::DatapointSubType_14_35:
			return Datapoint("DPST-14-35", "35", "DPT_Value_Heat_Capacity", "heat capacity (J/K)", "32");
		case DatapointTypes::DatapointSubType_14_36:
			return Datapoint("DPST-14-36", "36", "DPT_Value_Heat_FlowRate", "heat flow rate (W)", "32");
		case DatapointTypes::DatapointSubType_14_37:
			return Datapoint("DPST-14-37", "37", "DPT_Value_Heat_Quantity", "heat quantity", "32");
		case DatapointTypes::DatapointSubType_14_38:
			return Datapoint("DPST-14-38", "38", "DPT_Value_Impedance", "impedance ()", "32");
		case DatapointTypes::DatapointSubType_14_39:
			return Datapoint("DPST-14-39", "39", "DPT_Value_Length", "length (m)", "32");
		case DatapointTypes::DatapointSubType_14_40:
			return Datapoint("DPST-14-40", "40", "DPT_Value_Light_Quantity", "light quantity (J)", "32");
		case DatapointTypes::DatapointSubType_14_41:
			return Datapoint("DPST-14-41", "41", "DPT_Value_Luminance", "luminance (cd/m)", "32");
		case DatapointTypes::DatapointSubType_14_42:
			return Datapoint("DPST-14-42", "42", "DPT_Value_Luminous_Flux", "luminous flux (lm)", "32");
		case DatapointTypes::DatapointSubType_14_43:
			return Datapoint("DPST-14-43", "43", "DPT_Value_Luminous_Intensity", "luminous intensity (cd)", "32");
		case DatapointTypes::DatapointSubType_14_44:
			return Datapoint("DPST-14-44", "44", "DPT_Value_Magnetic_FieldStrength", "magnetic field strength (A/m)", "32");
		case DatapointTypes::DatapointSubType_14_45:
			return Datapoint("DPST-14-45", "45", "DPT_Value_Magnetic_Flux", "magnetic flux (Wb)", "32");
		case DatapointTypes::DatapointSubType_14_46:
			return Datapoint("DPST-14-46", "46", "DPT_Value_Magnetic_FluxDensity", "magnetic flux density (T)", "32");
		case DatapointTypes::DatapointSubType_14_47:
			return Datapoint("DPST-14-47", "47", "DPT_Value_Magnetic_Moment", "magnetic moment (Am)", "32");
		case DatapointTypes::DatapointSubType_14_48:
			return Datapoint("DPST-14-48", "48", "DPT_Value_Magnetic_Polarization", "magnetic polarization (T)", "32");
		case DatapointTypes::DatapointSubType_14_49:
			return Datapoint("DPST-14-49", "49", "DPT_Value_Magnetization", "magnetization (A/m)", "32");
		case DatapointTypes::DatapointSubType_14_50:
			return Datapoint("DPST-14-50", "50", "DPT_Value_MagnetomotiveForce", "magnetomotive force (A)", "32");
		case DatapointTypes::DatapointSubType_14_51:
			return Datapoint("DPST-14-51", "51", "DPT_Value_Mass", "mass (kg)", "32");
		case DatapointTypes::DatapointSubType_14_52:
			return Datapoint("DPST-14-52", "52", "DPT_Value_MassFlux", "mass flux (kg/s)", "32");
		case DatapointTypes::DatapointSubType_14_53:
			return Datapoint("DPST-14-53", "53", "DPT_Value_Momentum", "momentum (N/s)", "32");
		case DatapointTypes::DatapointSubType_14_54:
			return Datapoint("DPST-14-54", "54", "DPT_Value_Phase_AngleRad", "phase angle (rad)", "32");
		case DatapointTypes::DatapointSubType_14_55:
			return Datapoint("DPST-14-55", "55", "DPT_Value_Phase_AngleDeg", "phase angle ()", "32");
		case DatapointTypes::DatapointSubType_14_56:
			return Datapoint("DPST-14-56", "56", "DPT_Value_Power", "power (W)", "32");
		case DatapointTypes::DatapointSubType_14_57:
			return Datapoint("DPST-14-57", "57", "DPT_Value_Power_Factor", "power factor (cos )", "32");
		case DatapointTypes::DatapointSubType_14_58:
			return Datapoint("DPST-14-58", "58", "DPT_Value_Pressure", "pressure (Pa)", "32");
		case DatapointTypes::DatapointSubType_14_59:
			return Datapoint("DPST-14-59", "59", "DPT_Value_Reactance", "reactance ()", "32");
		case DatapointTypes::DatapointSubType_14_60:
			return Datapoint("DPST-14-60", "60", "DPT_Value_Resistance", "resistance ()", "32");
		case DatapointTypes::DatapointSubType_14_61:
			return Datapoint("DPST-14-61", "61", "DPT_Value_Resistivity", "resistivity (m)", "32");
		case DatapointTypes::DatapointSubType_14_62:
			return Datapoint("DPST-14-62", "62", "DPT_Value_SelfInductance", "self inductance (H)", "32");
		case DatapointTypes::DatapointSubType_14_63:
			return Datapoint("DPST-14-63", "63", "DPT_Value_SolidAngle", "solid angle (sr)", "32");
		case DatapointTypes::DatapointSubType_14_64:
			return Datapoint("DPST-14-64", "64", "DPT_Value_Sound_Intensity", "sound intensity (W/m)", "32");
		case DatapointTypes::DatapointSubType_14_65:
			return Datapoint("DPST-14-65", "65", "DPT_Value_Speed", "speed (m/s)", "32");
		case DatapointTypes::DatapointSubType_14_66:
			return Datapoint("DPST-14-66", "66", "DPT_Value_Stress", "stress (Pa)", "32");
		case DatapointTypes::DatapointSubType_14_67:
			return Datapoint("DPST-14-67", "67", "DPT_Value_Surface_Tension", "surface tension (N/m)", "32");
		case DatapointTypes::DatapointSubType_14_68:
			return Datapoint("DPST-14-68", "68", "DPT_Value_Common_Temperature", "temperature (C)", "32");
		case DatapointTypes::DatapointSubType_14_69:
			return Datapoint("DPST-14-69", "69", "DPT_Value_Absolute_Temperature", "temperature absolute (C)", "32");
		case DatapointTypes::DatapointSubType_14_70:
			return Datapoint("DPST-14-70", "70", "DPT_Value_TemperatureDifference", "temperature difference (K)", "32");
		case DatapointTypes::DatapointSubType_14_71:
			return Datapoint("DPST-14-71", "71", "DPT_Value_Thermal_Capacity", "thermal capacity (J/K)", "32");
		case DatapointTypes::DatapointSubType_14_72:
			return Datapoint("DPST-14-72", "72", "DPT_Value_Thermal_Conductivity", "thermal conductivity (W/mK)", "32");
		case DatapointTypes::DatapointSubType_14_73:
			return Datapoint("DPST-14-73", "73", "DPT_Value_ThermoelectricPower", "thermoelectric power (V/K)", "32");
		case DatapointTypes::DatapointSubType_14_74:
			return Datapoint("DPST-14-74", "74", "DPT_Value_Time", "time (s)", "32");
		case DatapointTypes::DatapointSubType_14_75:
			return Datapoint("DPST-14-75", "75", "DPT_Value_Torque", "torque (Nm)", "32");
		case DatapointTypes::DatapointSubType_14_76:
			return Datapoint("DPST-14-76", "76", "DPT_Value_Volume", "volume (m)", "32");
		case DatapointTypes::DatapointSubType_14_77:
			return Datapoint("DPST-14-77", "77", "DPT_Value_Volume_Flux", "volume flux (m/s)", "32");
		case DatapointTypes::DatapointSubType_14_78:
			return Datapoint("DPST-14-78", "78", "DPT_Value_Weight", "weight (N)", "32");
		case DatapointTypes::DatapointSubType_14_79:
			return Datapoint("DPST-14-79", "79", "DPT_Value_Work", "work (J)", "32");

		case DatapointTypes::DatapointType_15:
			return Datapoint("DPT-15", "15", "15.xxx", "entrance access", "32");
		case DatapointTypes::DatapointSubType_15_0:
			return Datapoint("DPST-15-0", "0", "DPT_Access_Data", "entrance access", "32");

		case DatapointTypes::DatapointType_16:
			return Datapoint("DPT-16", "16", "16.xxx", "character string", "112");
		case DatapointTypes::DatapointSubType_16_0:
			return Datapoint("DPST-16-0", "0", "DPT_String_ASCII", "Character String (ASCII)", "112");
		case DatapointTypes::DatapointSubType_16_1:
			return Datapoint("DPST-16-1", "1", "DPT_String_8859_1", "Character String (ISO 8859-1)", "112");

		case DatapointTypes::DatapointType_17:
			return Datapoint("DPT-17", "17", "17.xxx", "scene number", "8");
		case DatapointTypes::DatapointSubType_17_1:
			return Datapoint("DPST-17-1", "1", "DPT_SceneNumber", "scene number", "8");

		case DatapointTypes::DatapointType_18:
			return Datapoint("DPT-18", "18", "18.xxx", "scene control", "8");
		case DatapointTypes::DatapointSubType_18_1:
			return Datapoint("DPST-18-1", "1", "DPT_SceneControl", "scene control", "8");

		case DatapointTypes::DatapointType_19:
			return Datapoint("DPT-19", "19", "19.xxx", "Date Time", "64");
		case DatapointTypes::DatapointSubType_19_1:
			return Datapoint("DPST-19-1", "1", "DPT_DateTime", "date time", "64");

		case DatapointTypes::DatapointType_20:
			return Datapoint("DPT-20", "20", "20.xxx", "1-byte", "8");
		case DatapointTypes::DatapointSubType_20_1:
			return Datapoint("DPST-20-1", "1", "DPT_SCLOMode", "SCLO mode", "8");
		case DatapointTypes::DatapointSubType_20_2:
			return Datapoint("DPST-20-2", "2", "DPT_BuildingMode", "building mode", "8");
		case DatapointTypes::DatapointSubType_20_3:
			return Datapoint("DPST-20-3", "3", "DPT_OccMode", "occupied", "8");
		case DatapointTypes::DatapointSubType_20_4:
			return Datapoint("DPST-20-4", "4", "DPT_Priority", "priority", "8");
		case DatapointTypes::DatapointSubType_20_5:
			return Datapoint("DPST-20-5", "5", "DPT_LightApplicationMode", "light application mode", "8");
		case DatapointTypes::DatapointSubType_20_6:
			return Datapoint("DPST-20-6", "6", "ApplicationArea", "light application area", "8");
		case DatapointTypes::DatapointSubType_20_7:
			return Datapoint("DPST-20-7", "7", "DPT_AlarmClassType", "alarm class", "8");
		case DatapointTypes::DatapointSubType_20_8:
			return Datapoint("DPST-20-8", "8", "PSUMode", "PSU mode", "8");
		case DatapointTypes::DatapointSubType_20_11:
			return Datapoint("DPST-20-11", "11", "DPT_ErrorClass_System", "system error class", "8");
		case DatapointTypes::DatapointSubType_20_12:
			return Datapoint("DPST-20-12", "12", "DPT_ErrorClass_HVAC", "HVAC error class", "8");
		case DatapointTypes::DatapointSubType_20_13:
			return Datapoint("DPST-20-13", "13", "DPT_Time_Delay", "time delay", "8");
		case DatapointTypes::DatapointSubType_20_14:
			return Datapoint("DPST-20-14", "14", "DPT_Beaufort_Wind_Force_Scale", "wind force scale (0..12)", "8");
		case DatapointTypes::DatapointSubType_20_17:
			return Datapoint("DPST-20-17", "17", "DPT_SensorSelect", "sensor mode", "8");
		case DatapointTypes::DatapointSubType_20_20:
			return Datapoint("DPST-20-20", "20", "DPT_ActuatorConnectType", "actuator connect type", "8");
		case DatapointTypes::DatapointSubType_20_100:
			return Datapoint("DPST-20-100", "100", "DPT_FuelType", "fuel type", "8");
		case DatapointTypes::DatapointSubType_20_101:
			return Datapoint("DPST-20-101", "101", "DPT_BurnerType", "burner type", "8");
		case DatapointTypes::DatapointSubType_20_102:
			return Datapoint("DPST-20-102", "102", "DPT_HVACMode", "HVAC mode", "8");
		case DatapointTypes::DatapointSubType_20_103:
			return Datapoint("DPST-20-103", "103", "DPT_DHWMode", "DHW mode", "8");
		case DatapointTypes::DatapointSubType_20_104:
			return Datapoint("DPST-20-104", "104", "DPT_LoadPriority", "load priority", "8");
		case DatapointTypes::DatapointSubType_20_105:
			return Datapoint("DPST-20-105", "105", "DPT_HVACContrMode", "HVAC control mode", "8");
		case DatapointTypes::DatapointSubType_20_106:
			return Datapoint("DPST-20-106", "106", "DPT_HVACEmergMode", "HVAC emergency mode", "8");
		case DatapointTypes::DatapointSubType_20_107:
			return Datapoint("DPST-20-107", "107", "DPT_ChangeoverMode", "changeover mode", "8");
		case DatapointTypes::DatapointSubType_20_108:
			return Datapoint("DPST-20-108", "108", "DPT_ValveMode", "valve mode", "8");
		case DatapointTypes::DatapointSubType_20_109:
			return Datapoint("DPST-20-109", "109", "DPT_DamperMode", "damper mode", "8");
		case DatapointTypes::DatapointSubType_20_110:
			return Datapoint("DPST-20-110", "110", "DPT_HeaterMode", "heater mode", "8");
		case DatapointTypes::DatapointSubType_20_111:
			return Datapoint("DPST-20-111", "111", "DPT_FanMode", "fan mode", "8");
		case DatapointTypes::DatapointSubType_20_112:
			return Datapoint("DPST-20-112", "112", "DPT_MasterSlaveMode", "master/slave mode", "8");
		case DatapointTypes::DatapointSubType_20_113:
			return Datapoint("DPST-20-113", "113", "DPT_StatusRoomSetp", "status room setpoint", "8");
		case DatapointTypes::DatapointSubType_20_114:
			return Datapoint("DPST-20-114", "114", "DPT_Metering_DeviceType", "metering device type", "8");
		case DatapointTypes::DatapointSubType_20_120:
			return Datapoint("DPST-20-120", "120", "DPT_ADAType", "ADA type", "8");
		case DatapointTypes::DatapointSubType_20_121:
			return Datapoint("DPST-20-121", "121", "DPT_BackupMode", "backup mode", "8");
		case DatapointTypes::DatapointSubType_20_122:
			return Datapoint("DPST-20-122", "122", "DPT_StartSynchronization", "start syncronization type", "8");
		case DatapointTypes::DatapointSubType_20_600:
			return Datapoint("DPST-20-600", "600", "DPT_Behaviour_Lock_Unlock", "behavior lock/unlock", "8");
		case DatapointTypes::DatapointSubType_20_601:
			return Datapoint("DPST-20-601", "601", "DPT_Behaviour_Bus_Power_Up_Down", "behavior bus power up/down", "8");
		case DatapointTypes::DatapointSubType_20_602:
			return Datapoint("DPST-20-602", "602", "DPT_DALI_Fade_Time", "dali fade time", "8");
		case DatapointTypes::DatapointSubType_20_603:
			return Datapoint("DPST-20-603", "603", "DPT_BlinkingMode", "blink mode", "8");
		case DatapointTypes::DatapointSubType_20_604:
			return Datapoint("DPST-20-604", "604", "DPT_LightControlMode", "light control mode", "8");
		case DatapointTypes::DatapointSubType_20_605:
			return Datapoint("DPST-20-605", "605", "DPT_SwitchPBModel", "PB switch mode", "8");
		case DatapointTypes::DatapointSubType_20_606:
			return Datapoint("DPST-20-606", "606", "DPT_PBAction", "PB action mode", "8");
		case DatapointTypes::DatapointSubType_20_607:
			return Datapoint("DPST-20-607", "607", "DPT_DimmPBModel", "PB dimm mode", "8");
		case DatapointTypes::DatapointSubType_20_608:
			return Datapoint("DPST-20-608", "608", "DPT_SwitchOnMode", "switch on mode", "8");
		case DatapointTypes::DatapointSubType_20_609:
			return Datapoint("DPST-20-609", "609", "DPT_LoadTypeSet", "load type", "8");
		case DatapointTypes::DatapointSubType_20_610:
			return Datapoint("DPST-20-610", "610", "DPT_LoadTypeDetected", "load type detection", "8");
		case DatapointTypes::DatapointSubType_20_801:
			return Datapoint("DPST-20-801", "801", "DPT_SABExcept-Behaviour", "SAB except behavior", "8");
		case DatapointTypes::DatapointSubType_20_802:
			return Datapoint("DPST-20-802", "802", "DPT_SABBehaviour_Lock_Unlock", "SAB behavior on lock/unlock", "8");
		case DatapointTypes::DatapointSubType_20_803:
			return Datapoint("DPST-20-803", "803", "DPT_SSSBMode", "SSSB mode", "8");
		case DatapointTypes::DatapointSubType_20_804:
			return Datapoint("DPST-20-804", "804", "DPT_BlindsControlMode", "blinds control mode", "8");
		case DatapointTypes::DatapointSubType_20_1000:
			return Datapoint("DPST-20-1000", "1000", "DPT_CommMode", "communication mode", "8");
		case DatapointTypes::DatapointSubType_20_1001:
			return Datapoint("DPST-20-1001", "1001", "DPT_AddInfoTypes", "additional information type", "8");
		case DatapointTypes::DatapointSubType_20_1002:
			return Datapoint("DPST-20-1002", "1002", "DPT_RF_ModeSelect", "RF mode selection", "8");
		case DatapointTypes::DatapointSubType_20_1003:
			return Datapoint("DPST-20-1003", "1003", "DPT_RF_FilterSelect", "RF filter mode selection", "8");

		case DatapointTypes::DatapointType_21:
			return Datapoint("DPT-21", "21", "21.xxx", "8-bit set", "8");
		case DatapointTypes::DatapointSubType_21_1:
			return Datapoint("DPST-21-1", "1", "DPT_StatusGen", "general status", "8");
		case DatapointTypes::DatapointSubType_21_2:
			return Datapoint("DPST-21-2", "2", "DPT_Device_Control", "device control", "8");
		case DatapointTypes::DatapointSubType_21_100:
			return Datapoint("DPST-21-100", "100", "DPT_ForceSign", "forcing signal", "8");
		case DatapointTypes::DatapointSubType_21_101:
			return Datapoint("DPST-21-101", "101", "DPT_ForceSignCool", "forcing signal cool", "8");
		case DatapointTypes::DatapointSubType_21_102:
			return Datapoint("DPST-21-102", "102", "DPT_StatusRHC", "room heating controller status", "8");
		case DatapointTypes::DatapointSubType_21_103:
			return Datapoint("DPST-21-103", "103", "DPT_StatusSDHWC", "solar DHW controller status", "8");
		case DatapointTypes::DatapointSubType_21_104:
			return Datapoint("DPST-21-104", "104", "DPT_FuelTypeSet", "fuel type set", "8");
		case DatapointTypes::DatapointSubType_21_105:
			return Datapoint("DPST-21-105", "105", "DPT_StatusRCC", "room cooling controller status", "8");
		case DatapointTypes::DatapointSubType_21_106:
			return Datapoint("DPST-21-106", "106", "DPT_StatusAHU", "ventilation controller status", "8");
		case DatapointTypes::DatapointSubType_21_601:
			return Datapoint("DPST-21-601", "601", "DPT_LightActuatorErrorInfo", "lighting actuator error information", "8");
		case DatapointTypes::DatapointSubType_21_1000:
			return Datapoint("DPST-21-1000", "1000", "DPT_RF_ModeInfo", "RF communication mode info", "8");
		case DatapointTypes::DatapointSubType_21_1001:
			return Datapoint("DPST-21-1001", "1001", "DPT_RF_FilterInfo", "cEMI server supported RF filtering modes", "8");
		case DatapointTypes::DatapointSubType_21_1010:
			return Datapoint("DPST-21-1010", "1010", "DPT_Channel_Activation_8", "channel activation for 8 channels", "8");

		case DatapointTypes::DatapointType_22:
			return Datapoint("DPT-22", "22", "22.xxx", "16-bit set", "16");
		case DatapointTypes::DatapointSubType_22_100:
			return Datapoint("DPST-22-100", "100", "DPT_StatusDHWC", "DHW controller status", "16");
		case DatapointTypes::DatapointSubType_22_101:
			return Datapoint("DPST-22-101", "101", "DPT_StatusRHCC", "RHCC status", "16");
		case DatapointTypes::DatapointSubType_22_1000:
			return Datapoint("DPST-22-1000", "1000", "DPT_Media", "media", "16");
		case DatapointTypes::DatapointSubType_22_1010:
			return Datapoint("DPST-22-1010", "1010", "DPT_Channel_Activation_16", "channel activation for 16 channels", "16");

		case DatapointTypes::DatapointType_23:
			return Datapoint("DPT-23", "23", "23.xxx", "2-bit set", "2");
		case DatapointTypes::DatapointSubType_23_1:
			return Datapoint("DPST-23-1", "1", "DPT_OnOffAction", "on/off action", "2");
		case DatapointTypes::DatapointSubType_23_2:
			return Datapoint("DPST-23-2", "2", "DPT_Alarm_Reaction", "alarm reaction", "2");
		case DatapointTypes::DatapointSubType_23_3:
			return Datapoint("DPST-23-3", "3", "DPT_UpDown_Action", "up/down action", "2");
		case DatapointTypes::DatapointSubType_23_102:
			return Datapoint("DPST-23-102", "102", "DPT_HVAC_PB_Action", "HVAC push button action", "2");

		case DatapointTypes::DatapointType_25:
			return Datapoint("DPT-25", "25", "25.xxx", "2-nibble set", "8");
		case DatapointTypes::DatapointSubType_25_1000:
			return Datapoint("DPST-25-1000", "1000", "DPT_DoubleNibble", "busy/nak repetitions", "8");

		case DatapointTypes::DatapointType_26:
			return Datapoint("DPT-26", "26", "26.xxx", "8-bit set", "8");
		case DatapointTypes::DatapointSubType_26_1:
			return Datapoint("DPST-26-1", "1", "DPT_SceneInfo", "scene information", "8");

		case DatapointTypes::DatapointType_27:
			return Datapoint("DPT-27", "27", "27.xxx", "32-bit set", "32");
		case DatapointTypes::DatapointSubType_27_1:
			return Datapoint("DPST-27-1", "1", "DPT_CombinedInfoOnOff", "bit-combined info on/off", "32");

		case DatapointTypes::DatapointType_29:
			return Datapoint("DPT-29", "29", "29.xxx", "electrical energy", "64");
		case DatapointTypes::DatapointSubType_29_10:
			return Datapoint("DPST-29-10", "10", "DPT_ActiveEnergy_V64", "active energy (Wh)", "64");
		case DatapointTypes::DatapointSubType_29_11:
			return Datapoint("DPST-29-11", "11", "DPT_ApparantEnergy_V64", "apparant energy (VAh)", "64");
		case DatapointTypes::DatapointSubType_29_12:
			return Datapoint("DPST-29-12", "12", "DPT_ReactiveEnergy_V64", "reactive energy (VARh)", "64");

		case DatapointTypes::DatapointType_30:
			return Datapoint("DPT-30", "30", "30.xxx", "24 times channel activation", "24");
		case DatapointTypes::DatapointSubType_30_1010:
			return Datapoint("DPST-30-1010", "1010", "DPT_Channel_Activation_24", "activation state 0..23", "24");

		case DatapointTypes::DatapointType_206:
			return Datapoint("DPT-206", "206", "206.xxx", "16-bit unsigned value & 8-bit enum", "24");
		case DatapointTypes::DatapointSubType_206_100:
			return Datapoint("DPST-206-100", "100", "DPT_HVACModeNext", "time delay & HVAC mode", "24");
		case DatapointTypes::DatapointSubType_206_102:
			return Datapoint("DPST-206-102", "102", "DPT_DHWModeNext", "time delay & DHW mode", "24");
		case DatapointTypes::DatapointSubType_206_104:
			return Datapoint("DPST-206-104", "104", "DPT_OccModeNext", "time delay & occupancy mode", "24");
		case DatapointTypes::DatapointSubType_206_105:
			return Datapoint("DPST-206-105", "105", "DPT_BuildingModeNext", "time delay & building mode", "24");

		case DatapointTypes::DatapointType_217:
			return Datapoint("DPT-217", "217", "217.xxx", "datapoint type version", "16");
		case DatapointTypes::DatapointSubType_217_1:
			return Datapoint("DPST-217-1", "1", "DPT_Version", "DPT version", "16");

		case DatapointTypes::DatapointType_219:
			return Datapoint("DPT-219", "219", "219.xxx", "alarm info", "48");
		case DatapointTypes::DatapointSubType_219_1:
			return Datapoint("DPST-219-1", "1", "DPT_AlarmInfo", "alarm info", "48");

		case DatapointTypes::DatapointType_222:
			return Datapoint("DPT-222", "222", "222.xxx", "3x 2-byte float value", "48");
		case DatapointTypes::DatapointSubType_222_100:
			return Datapoint("DPST-222-100", "100", "DPT_TempRoomSetpSetF16[3]", "room temperature setpoint", "48");
		case DatapointTypes::DatapointSubType_222_101:
			return Datapoint("DPST-222-101", "101", "DPT_TempRoomSetpSetShiftF16[3]", "room temperature setpoint shift", "48");

		case DatapointTypes::DatapointType_229:
			return Datapoint("DPT-229", "229", "229.xxx", "4-1-1 byte combined information", "48");
		case DatapointTypes::DatapointSubType_229_1:
			return Datapoint("DPST-229-1", "1", "DPT_MeteringValue", "metering value (value,encoding,cmd)", "48");

		case DatapointTypes::DatapointType_230:
			return Datapoint("DPT-230", "230", "230.xxx", "MBus address", "64");
		case DatapointTypes::DatapointSubType_230_1000:
			return Datapoint("DPST-230-1000", "1000", "DPT_MBus_Address", "MBus address", "64");

		case DatapointTypes::DatapointType_232:
			return Datapoint("DPT-232", "232", "232.xxx", "3-byte colour RGB", "24");
		case DatapointTypes::DatapointSubType_232_600:
			return Datapoint("DPST-232-600", "600", "DPT_Colour_RGB", "RGB value 3x(0..255)", "24");

		case DatapointTypes::DatapointType_234:
			return Datapoint("DPT-234", "234", "234.xxx", "language code ISO 639-1", "16");
		case DatapointTypes::DatapointSubType_234_1:
			return Datapoint("DPST-234-1", "1", "DPT_LanguageCodeAlpha2_ASCII", "language code (ASCII)", "16");

		case DatapointTypes::DatapointType_237:
			return Datapoint("DPT-237", "237", "237.xxx", "configuration/ diagnostics", "16");
		case DatapointTypes::DatapointSubType_237_600:
			return Datapoint("DPST-237-600", "600", "DPT_DALI_Control_Gear_Diagnostic", "diagnostic value", "16");

		case DatapointTypes::DatapointType_238:
			return Datapoint("DPT-238", "238", "238.xxx", "configuration/ diagnostics", "8");
		case DatapointTypes::DatapointSubType_238_600:
			return Datapoint("DPST-238-600", "600", "DPT_DALI_Diagnostics", "diagnostic value", "8");


		default:
			throw Exception("Unsupported Datapoint Type");
	}
}

Datapoint DatapointFactory::create(const std::string& datapointId)
{
	return create(DatapointTypes::getTypeFromId(datapointId));
}
