//
// Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//


#ifndef __KDRIVE_KNX_DEFINES_DATAPOINT_TYPES_H__
#define __KDRIVE_KNX_DEFINES_DATAPOINT_TYPES_H__

#include "kdrive/knx/Config.h"
#include <string>

namespace kdrive
{
namespace knx
{

struct kdriveKnx_API DatapointTypes
{
	enum Types
	{
		DatapointType_1, /*!< Id="DPT-1" Number="1" Name="1.xxx" Text="1-bit" SizeInBit="1" */
		DatapointSubType_1_1, /*!< Id="DPST-1-1" Number="1" Name="DPT_Switch" Text="switch" */
		DatapointSubType_1_2, /*!< Id="DPST-1-2" Number="2" Name="DPT_Bool" Text="boolean" */
		DatapointSubType_1_3, /*!< Id="DPST-1-3" Number="3" Name="DPT_Enable" Text="enable" */
		DatapointSubType_1_4, /*!< Id="DPST-1-4" Number="4" Name="DPT_Ramp" Text="ramp" */
		DatapointSubType_1_5, /*!< Id="DPST-1-5" Number="5" Name="DPT_Alarm" Text="alarm" */
		DatapointSubType_1_6, /*!< Id="DPST-1-6" Number="6" Name="DPT_BinaryValue" Text="binary value" */
		DatapointSubType_1_7, /*!< Id="DPST-1-7" Number="7" Name="DPT_Step" Text="step" */
		DatapointSubType_1_8, /*!< Id="DPST-1-8" Number="8" Name="DPT_UpDown" Text="up/down" */
		DatapointSubType_1_9, /*!< Id="DPST-1-9" Number="9" Name="DPT_OpenClose" Text="open/close" */
		DatapointSubType_1_10, /*!< Id="DPST-1-10" Number="10" Name="DPT_Start" Text="start/stop" */
		DatapointSubType_1_11, /*!< Id="DPST-1-11" Number="11" Name="DPT_State" Text="state" */
		DatapointSubType_1_12, /*!< Id="DPST-1-12" Number="12" Name="DPT_Invert" Text="invert" */
		DatapointSubType_1_13, /*!< Id="DPST-1-13" Number="13" Name="DPT_DimSendStyle" Text="dim send style" */
		DatapointSubType_1_14, /*!< Id="DPST-1-14" Number="14" Name="DPT_InputSource" Text="input source" */
		DatapointSubType_1_15, /*!< Id="DPST-1-15" Number="15" Name="DPT_Reset" Text="reset" */
		DatapointSubType_1_16, /*!< Id="DPST-1-16" Number="16" Name="DPT_Ack" Text="acknowledge" */
		DatapointSubType_1_17, /*!< Id="DPST-1-17" Number="17" Name="DPT_Trigger" Text="trigger" */
		DatapointSubType_1_18, /*!< Id="DPST-1-18" Number="18" Name="DPT_Occupancy" Text="occupancy" */
		DatapointSubType_1_19, /*!< Id="DPST-1-19" Number="19" Name="DPT_Window_Door" Text="window/door" */
		DatapointSubType_1_21, /*!< Id="DPST-1-21" Number="21" Name="DPT_LogicalFunction" Text="logical function" */
		DatapointSubType_1_22, /*!< Id="DPST-1-22" Number="22" Name="DPT_Scene_AB" Text="scene" */
		DatapointSubType_1_23, /*!< Id="DPST-1-23" Number="23" Name="DPT_ShutterBlinds_Mode" Text="shutter/blinds mode" */
		DatapointSubType_1_100, /*!< Id="DPST-1-100" Number="100" Name="DPT_Heat_Cool" Text="cooling/heating" */

		DatapointType_2, /*!< Id="DPT-2" Number="2" Name="2.xxx" Text="1-bit controlled" SizeInBit="2" */
		DatapointSubType_2_1, /*!< Id="DPST-2-1" Number="1" Name="DPT_Switch_Control" Text="switch control" */
		DatapointSubType_2_2, /*!< Id="DPST-2-2" Number="2" Name="DPT_Bool_Control" Text="boolean control" */
		DatapointSubType_2_3, /*!< Id="DPST-2-3" Number="3" Name="DPT_Enable_Control" Text="enable control" */
		DatapointSubType_2_4, /*!< Id="DPST-2-4" Number="4" Name="DPT_Ramp_Control" Text="ramp control" */
		DatapointSubType_2_5, /*!< Id="DPST-2-5" Number="5" Name="DPT_Alarm_Control" Text="alarm control" */
		DatapointSubType_2_6, /*!< Id="DPST-2-6" Number="6" Name="DPT_BinaryValue_Control" Text="binary value control" */
		DatapointSubType_2_7, /*!< Id="DPST-2-7" Number="7" Name="DPT_Step_Control" Text="step control" */
		DatapointSubType_2_8, /*!< Id="DPST-2-8" Number="8" Name="DPT_Direction1_Control" Text="direction control 1" */
		DatapointSubType_2_9, /*!< Id="DPST-2-9" Number="9" Name="DPT_Direction2_Control" Text="direction control 2" */
		DatapointSubType_2_10, /*!< Id="DPST-2-10" Number="10" Name="DPT_Start_Control" Text="start control" */
		DatapointSubType_2_11, /*!< Id="DPST-2-11" Number="11" Name="DPT_State_Control" Text="state control" */
		DatapointSubType_2_12, /*!< Id="DPST-2-12" Number="12" Name="DPT_Invert_Control" Text="invert control" */

		DatapointType_3, /*!< Id="DPT-3" Number="3" Name="3.xxx" Text="3-bit controlled" SizeInBit="4" */
		DatapointSubType_3_7, /*!< Id="DPST-3-7" Number="7" Name="DPT_Control_Dimming" Text="dimming control" */
		DatapointSubType_3_8, /*!< Id="DPST-3-8" Number="8" Name="DPT_Control_Blinds" Text="blind control" */

		DatapointType_4, /*!< Id="DPT-4" Number="4" Name="4.xxx" Text="character" SizeInBit="8" */
		DatapointSubType_4_1, /*!< Id="DPST-4-1" Number="1" Name="DPT_Char_ASCII" Text="character (ASCII)" */
		DatapointSubType_4_2, /*!< Id="DPST-4-2" Number="2" Name="DPT_Char_8859_1" Text="character (ISO 8859-1)" */

		DatapointType_5, /*!< Id="DPT-5" Number="5" Name="5.xxx" Text="8-bit unsigned value" SizeInBit="8" */
		DatapointSubType_5_1, /*!< Id="DPST-5-1" Number="1" Name="DPT_Scaling" Text="percentage (0..100%)" */
		DatapointSubType_5_3, /*!< Id="DPST-5-3" Number="3" Name="DPT_Angle" Text="angle (degrees)" */
		DatapointSubType_5_4, /*!< Id="DPST-5-4" Number="4" Name="DPT_Percent_U8" Text="percentage (0..255%)" */
		DatapointSubType_5_5, /*!< Id="DPST-5-5" Number="5" Name="DPT_DecimalFactor" Text="ratio (0..255)" */
		DatapointSubType_5_6, /*!< Id="DPST-5-6" Number="6" Name="DPT_Tariff" Text="tariff (0..255)" */
		DatapointSubType_5_10, /*!< Id="DPST-5-10" Number="10" Name="DPT_Value_1_Ucount" Text="counter pulses (0..255)" */

		DatapointType_6, /*!< Id="DPT-6" Number="6" Name="6.xxx" Text="8-bit signed value" SizeInBit="8" */
		DatapointSubType_6_1, /*!< Id="DPST-6-1" Number="1" Name="DPT_Percent_V8" Text="percentage (-128..127%)" */
		DatapointSubType_6_10, /*!< Id="DPST-6-10" Number="10" Name="DPT_Value_1_Count" Text="counter pulses (-128..127)" */
		DatapointSubType_6_20, /*!< Id="DPST-6-20" Number="20" Name="DPT_Status_Mode3" Text="status with mode" */

		DatapointType_7, /*!< Id="DPT-7" Number="7" Name="7.xxx" Text="2-byte unsigned value" SizeInBit="16" */
		DatapointSubType_7_1, /*!< Id="DPST-7-1" Number="1" Name="DPT_Value_2_Ucount" Text="pulses" */
		DatapointSubType_7_2, /*!< Id="DPST-7-2" Number="2" Name="DPT_TimePeriodMsec" Text="time (ms)" */
		DatapointSubType_7_3, /*!< Id="DPST-7-3" Number="3" Name="DPT_TimePeriod10Msec" Text="time (10 ms)" */
		DatapointSubType_7_4, /*!< Id="DPST-7-4" Number="4" Name="DPT_TimePeriod100Msec" Text="time (100 ms)" */
		DatapointSubType_7_5, /*!< Id="DPST-7-5" Number="5" Name="DPT_TimePeriodSec" Text="time (s)" */
		DatapointSubType_7_6, /*!< Id="DPST-7-6" Number="6" Name="DPT_TimePeriodMin" Text="time (min)" */
		DatapointSubType_7_7, /*!< Id="DPST-7-7" Number="7" Name="DPT_TimePeriodHrs" Text="time (h)" */
		DatapointSubType_7_10, /*!< Id="DPST-7-10" Number="10" Name="DPT_PropDataType" Text="property data type" */
		DatapointSubType_7_11, /*!< Id="DPST-7-11" Number="11" Name="DPT_Length_mm" Text="length (mm)" */
		DatapointSubType_7_12, /*!< Id="DPST-7-12" Number="12" Name="DPT_UElCurrentmA" Text="current (mA)" */
		DatapointSubType_7_13, /*!< Id="DPST-7-13" Number="13" Name="DPT_Brightness" Text="brightness (lux)" */

		DatapointType_8, /*!< Id="DPT-8" Number="8" Name="8.xxx" Text="2-byte signed value" SizeInBit="16" */
		DatapointSubType_8_1, /*!< Id="DPST-8-1" Number="1" Name="DPT_Value_2_Count" Text="pulses difference" */
		DatapointSubType_8_2, /*!< Id="DPST-8-2" Number="2" Name="DPT_DeltaTimeMsec" Text="time lag (ms)" */
		DatapointSubType_8_3, /*!< Id="DPST-8-3" Number="3" Name="DPT_DeltaTime10Msec" Text="time lag(10 ms)" */
		DatapointSubType_8_4, /*!< Id="DPST-8-4" Number="4" Name="DPT_DeltaTime100Msec" Text="time lag (100 ms)" */
		DatapointSubType_8_5, /*!< Id="DPST-8-5" Number="5" Name="DPT_DeltaTimeSec" Text="time lag (s)" */
		DatapointSubType_8_6, /*!< Id="DPST-8-6" Number="6" Name="DPT_DeltaTimeMin" Text="time lag (min)" */
		DatapointSubType_8_7, /*!< Id="DPST-8-7" Number="7" Name="DPT_DeltaTimeHrs" Text="time lag (h)" */
		DatapointSubType_8_10, /*!< Id="DPST-8-10" Number="10" Name="DPT_Percent_V16" Text="percentage difference (%)" */
		DatapointSubType_8_11, /*!< Id="DPST-8-11" Number="11" Name="DPT_Rotation_Angle" Text="rotation angle ()" */

		DatapointType_9, /*!< Id="DPT-9" Number="9" Name="9.xxx" Text="2-byte float value" SizeInBit="16" */
		DatapointSubType_9_1, /*!< Id="DPST-9-1" Number="1" Name="DPT_Value_Temp" Text="temperature (C)" */
		DatapointSubType_9_2, /*!< Id="DPST-9-2" Number="2" Name="DPT_Value_Tempd" Text="temperature difference (K)" */
		DatapointSubType_9_3, /*!< Id="DPST-9-3" Number="3" Name="DPT_Value_Tempa" Text="kelvin/hour (K/h)" */
		DatapointSubType_9_4, /*!< Id="DPST-9-4" Number="4" Name="DPT_Value_Lux" Text="lux (Lux)" */
		DatapointSubType_9_5, /*!< Id="DPST-9-5" Number="5" Name="DPT_Value_Wsp" Text="speed (m/s)" */
		DatapointSubType_9_6, /*!< Id="DPST-9-6" Number="6" Name="DPT_Value_Pres" Text="pressure (Pa)" */
		DatapointSubType_9_7, /*!< Id="DPST-9-7" Number="7" Name="DPT_Value_Humidity" Text="humidity (%)" */
		DatapointSubType_9_8, /*!< Id="DPST-9-8" Number="8" Name="DPT_Value_AirQuality" Text="parts/million (ppm)" */
		DatapointSubType_9_9, /*!< Id="DPST-9-9" Number="9" Name="DPT_Value_AirFlow" Text="air flow (m/h)" */
		DatapointSubType_9_10, /*!< Id="DPST-9-10" Number="10" Name="DPT_Value_Time1" Text="time (s)" */
		DatapointSubType_9_11, /*!< Id="DPST-9-11" Number="11" Name="DPT_Value_Time2" Text="time (ms)" */
		DatapointSubType_9_20, /*!< Id="DPST-9-20" Number="20" Name="DPT_Value_Volt" Text="voltage (mV)" */
		DatapointSubType_9_21, /*!< Id="DPST-9-21" Number="21" Name="DPT_Value_Curr" Text="current (mA)" */
		DatapointSubType_9_22, /*!< Id="DPST-9-22" Number="22" Name="DPT_PowerDensity" Text="power density (W/m)" */
		DatapointSubType_9_23, /*!< Id="DPST-9-23" Number="23" Name="DPT_KelvinPerPercent" Text="kelvin/percent (K/%)" */
		DatapointSubType_9_24, /*!< Id="DPST-9-24" Number="24" Name="DPT_Power" Text="power (kW)" */
		DatapointSubType_9_25, /*!< Id="DPST-9-25" Number="25" Name="DPT_Value_Volume_Flow" Text="volume flow (l/h)" */
		DatapointSubType_9_26, /*!< Id="DPST-9-26" Number="26" Name="DPT_Rain_Amount" Text="rain amount (l/m)" */
		DatapointSubType_9_27, /*!< Id="DPST-9-27" Number="27" Name="DPT_Value_Temp_F" Text="temperature (F)" */
		DatapointSubType_9_28, /*!< Id="DPST-9-28" Number="28" Name="DPT_Value_Wsp_kmh" Text="wind speed (km/h)" */

		DatapointType_10, /*!< Id="DPT-10" Number="10" Name="10.xxx" Text="time" SizeInBit="24" */
		DatapointSubType_10_1, /*!< Id="DPST-10-1" Number="1" Name="DPT_TimeOfDay" Text="time of day" */

		DatapointType_11, /*!< Id="DPT-11" Number="11" Name="11.xxx" Text="date" SizeInBit="24" */
		DatapointSubType_11_1, /*!< Id="DPST-11-1" Number="1" Name="DPT_Date" Text="date" */

		DatapointType_12, /*!< Id="DPT-12" Number="12" Name="12.xxx" Text="4-byte unsigned value" SizeInBit="32" */
		DatapointSubType_12_1, /*!< Id="DPST-12-1" Number="1" Name="DPT_Value_4_Ucount" Text="counter pulses (unsigned)" */

		DatapointType_13, /*!< Id="DPT-13" Number="13" Name="13.xxx" Text="4-byte signed value" SizeInBit="32" */
		DatapointSubType_13_1, /*!< Id="DPST-13-1" Number="1" Name="DPT_Value_4_Count" Text="counter pulses (signed)" */
		DatapointSubType_13_2, /*!< Id="DPST-13-2" Number="2" Name="DPT_FlowRate_m3/h" Text="flow rate (m/h)" */
		DatapointSubType_13_10, /*!< Id="DPST-13-10" Number="10" Name="DPT_ActiveEnergy" Text="active energy (Wh)" */
		DatapointSubType_13_11, /*!< Id="DPST-13-11" Number="11" Name="DPT_ApparantEnergy" Text="apparent energy (VAh)" */
		DatapointSubType_13_12, /*!< Id="DPST-13-12" Number="12" Name="DPT_ReactiveEnergy" Text="reactive energy (VARh)" */
		DatapointSubType_13_13, /*!< Id="DPST-13-13" Number="13" Name="DPT_ActiveEnergy_kWh" Text="active energy (kWh)" */
		DatapointSubType_13_14, /*!< Id="DPST-13-14" Number="14" Name="DPT_ApparantEnergy_kVAh" Text="apparent energy (kVAh)" */
		DatapointSubType_13_15, /*!< Id="DPST-13-15" Number="15" Name="DPT_ReactiveEnergy_kVARh" Text="reactive energy (kVARh)" */
		DatapointSubType_13_100, /*!< Id="DPST-13-100" Number="100" Name="DPT_LongDeltaTimeSec" Text="time lag (s)" */

		DatapointType_14, /*!< Id="DPT-14" Number="14" Name="14.xxx" Text="4-byte float value" SizeInBit="32" */
		DatapointSubType_14_0, /*!< Id="DPST-14-0" Number="0" Name="DPT_Value_Acceleration" Text="acceleration (m/s)" */
		DatapointSubType_14_1, /*!< Id="DPST-14-1" Number="1" Name="DPT_Value_Acceleration_Angular" Text="angular acceleration (rad/s)" */
		DatapointSubType_14_2, /*!< Id="DPST-14-2" Number="2" Name="DPT_Value_Activation_Energy" Text="activation energy (J/mol)" */
		DatapointSubType_14_3, /*!< Id="DPST-14-3" Number="3" Name="DPT_Value_Activity" Text="radioactive activity (1/s)" */
		DatapointSubType_14_4, /*!< Id="DPST-14-4" Number="4" Name="DPT_Value_Mol" Text="amount of substance (mol)" */
		DatapointSubType_14_5, /*!< Id="DPST-14-5" Number="5" Name="DPT_Value_Amplitude" Text="amplitude" */
		DatapointSubType_14_6, /*!< Id="DPST-14-6" Number="6" Name="DPT_Value_AngleRad" Text="angle (radiant)" */
		DatapointSubType_14_7, /*!< Id="DPST-14-7" Number="7" Name="DPT_Value_AngleDeg" Text="angle (degree)" */
		DatapointSubType_14_8, /*!< Id="DPST-14-8" Number="8" Name="DPT_Value_Angular_Momentum" Text="angular momentum (Js)" */
		DatapointSubType_14_9, /*!< Id="DPST-14-9" Number="9" Name="DPT_Value_Angular_Velocity" Text="angular velocity (rad/s)" */
		DatapointSubType_14_10, /*!< Id="DPST-14-10" Number="10" Name="DPT_Value_Area" Text="area (m*m)" */
		DatapointSubType_14_11, /*!< Id="DPST-14-11" Number="11" Name="DPT_Value_Capacitance" Text="capacitance (F)" */
		DatapointSubType_14_12, /*!< Id="DPST-14-12" Number="12" Name="DPT_Value_Charge_DensitySurface" Text="flux density (C/m)" */
		DatapointSubType_14_13, /*!< Id="DPST-14-13" Number="13" Name="DPT_Value_Charge_DensityVolume" Text="charge density (C/m)" */
		DatapointSubType_14_14, /*!< Id="DPST-14-14" Number="14" Name="DPT_Value_Compressibility" Text="compressibility (m/N)" */
		DatapointSubType_14_15, /*!< Id="DPST-14-15" Number="15" Name="DPT_Value_Conductance" Text="conductance (S)" */
		DatapointSubType_14_16, /*!< Id="DPST-14-16" Number="16" Name="DPT_Value_Electrical_Conductivity" Text="conductivity  (S/m)" */
		DatapointSubType_14_17, /*!< Id="DPST-14-17" Number="17" Name="DPT_Value_Density" Text="density (kg/m)" */
		DatapointSubType_14_18, /*!< Id="DPST-14-18" Number="18" Name="DPT_Value_Electric_Charge" Text="electric charge (C)" */
		DatapointSubType_14_19, /*!< Id="DPST-14-19" Number="19" Name="DPT_Value_Electric_Current" Text="electric current (A)" */
		DatapointSubType_14_20, /*!< Id="DPST-14-20" Number="20" Name="DPT_Value_Electric_CurrentDensity" Text="electric current density (A/m)" */
		DatapointSubType_14_21, /*!< Id="DPST-14-21" Number="21" Name="DPT_Value_Electric_DipoleMoment" Text="electric dipole moment (Cm)" */
		DatapointSubType_14_22, /*!< Id="DPST-14-22" Number="22" Name="DPT_Value_Electric_Displacement" Text="electric displacement (C/m)" */
		DatapointSubType_14_23, /*!< Id="DPST-14-23" Number="23" Name="DPT_Value_Electric_FieldStrength" Text="electric field strength (V/m)" */
		DatapointSubType_14_24, /*!< Id="DPST-14-24" Number="24" Name="DPT_Value_Electric_Flux" Text="electric flux (C)" */
		DatapointSubType_14_25, /*!< Id="DPST-14-25" Number="25" Name="DPT_Value_Electric_FluxDensity" Text="electric flux density (C/m)" */
		DatapointSubType_14_26, /*!< Id="DPST-14-26" Number="26" Name="DPT_Value_Electric_Polarization" Text="electric polarization (C/m)" */
		DatapointSubType_14_27, /*!< Id="DPST-14-27" Number="27" Name="DPT_Value_Electric_Potential" Text="electric potential (V)" */
		DatapointSubType_14_28, /*!< Id="DPST-14-28" Number="28" Name="DPT_Value_Electric_PotentialDifference" Text="electric potential difference (V)" */
		DatapointSubType_14_29, /*!< Id="DPST-14-29" Number="29" Name="DPT_Value_ElectromagneticMoment" Text="electromagnetic moment (Am)" */
		DatapointSubType_14_30, /*!< Id="DPST-14-30" Number="30" Name="DPT_Value_Electromotive_Force" Text="electromotive force (V)" */
		DatapointSubType_14_31, /*!< Id="DPST-14-31" Number="31" Name="DPT_Value_Energy" Text="energy (J)" */
		DatapointSubType_14_32, /*!< Id="DPST-14-32" Number="32" Name="DPT_Value_Force" Text="force (N)" */
		DatapointSubType_14_33, /*!< Id="DPST-14-33" Number="33" Name="DPT_Value_Frequency" Text="frequency (Hz)" */
		DatapointSubType_14_34, /*!< Id="DPST-14-34" Number="34" Name="DPT_Value_Angular_Frequency" Text="angular frequency (rad/s)" */
		DatapointSubType_14_35, /*!< Id="DPST-14-35" Number="35" Name="DPT_Value_Heat_Capacity" Text="heat capacity (J/K)" */
		DatapointSubType_14_36, /*!< Id="DPST-14-36" Number="36" Name="DPT_Value_Heat_FlowRate" Text="heat flow rate (W)" */
		DatapointSubType_14_37, /*!< Id="DPST-14-37" Number="37" Name="DPT_Value_Heat_Quantity" Text="heat quantity" */
		DatapointSubType_14_38, /*!< Id="DPST-14-38" Number="38" Name="DPT_Value_Impedance" Text="impedance ()" */
		DatapointSubType_14_39, /*!< Id="DPST-14-39" Number="39" Name="DPT_Value_Length" Text="length (m)" */
		DatapointSubType_14_40, /*!< Id="DPST-14-40" Number="40" Name="DPT_Value_Light_Quantity" Text="light quantity (J)" */
		DatapointSubType_14_41, /*!< Id="DPST-14-41" Number="41" Name="DPT_Value_Luminance" Text="luminance (cd/m)" */
		DatapointSubType_14_42, /*!< Id="DPST-14-42" Number="42" Name="DPT_Value_Luminous_Flux" Text="luminous flux (lm)" */
		DatapointSubType_14_43, /*!< Id="DPST-14-43" Number="43" Name="DPT_Value_Luminous_Intensity" Text="luminous intensity (cd)" */
		DatapointSubType_14_44, /*!< Id="DPST-14-44" Number="44" Name="DPT_Value_Magnetic_FieldStrength" Text="magnetic field strength (A/m)" */
		DatapointSubType_14_45, /*!< Id="DPST-14-45" Number="45" Name="DPT_Value_Magnetic_Flux" Text="magnetic flux (Wb)" */
		DatapointSubType_14_46, /*!< Id="DPST-14-46" Number="46" Name="DPT_Value_Magnetic_FluxDensity" Text="magnetic flux density (T)" */
		DatapointSubType_14_47, /*!< Id="DPST-14-47" Number="47" Name="DPT_Value_Magnetic_Moment" Text="magnetic moment (Am)" */
		DatapointSubType_14_48, /*!< Id="DPST-14-48" Number="48" Name="DPT_Value_Magnetic_Polarization" Text="magnetic polarization (T)" */
		DatapointSubType_14_49, /*!< Id="DPST-14-49" Number="49" Name="DPT_Value_Magnetization" Text="magnetization (A/m)" */
		DatapointSubType_14_50, /*!< Id="DPST-14-50" Number="50" Name="DPT_Value_MagnetomotiveForce" Text="magnetomotive force (A)" */
		DatapointSubType_14_51, /*!< Id="DPST-14-51" Number="51" Name="DPT_Value_Mass" Text="mass (kg)" */
		DatapointSubType_14_52, /*!< Id="DPST-14-52" Number="52" Name="DPT_Value_MassFlux" Text="mass flux (kg/s)" */
		DatapointSubType_14_53, /*!< Id="DPST-14-53" Number="53" Name="DPT_Value_Momentum" Text="momentum (N/s)" */
		DatapointSubType_14_54, /*!< Id="DPST-14-54" Number="54" Name="DPT_Value_Phase_AngleRad" Text="phase angle (rad)" */
		DatapointSubType_14_55, /*!< Id="DPST-14-55" Number="55" Name="DPT_Value_Phase_AngleDeg" Text="phase angle ()" */
		DatapointSubType_14_56, /*!< Id="DPST-14-56" Number="56" Name="DPT_Value_Power" Text="power (W)" */
		DatapointSubType_14_57, /*!< Id="DPST-14-57" Number="57" Name="DPT_Value_Power_Factor" Text="power factor (cos )" */
		DatapointSubType_14_58, /*!< Id="DPST-14-58" Number="58" Name="DPT_Value_Pressure" Text="pressure (Pa)" */
		DatapointSubType_14_59, /*!< Id="DPST-14-59" Number="59" Name="DPT_Value_Reactance" Text="reactance ()" */
		DatapointSubType_14_60, /*!< Id="DPST-14-60" Number="60" Name="DPT_Value_Resistance" Text="resistance ()" */
		DatapointSubType_14_61, /*!< Id="DPST-14-61" Number="61" Name="DPT_Value_Resistivity" Text="resistivity (m)" */
		DatapointSubType_14_62, /*!< Id="DPST-14-62" Number="62" Name="DPT_Value_SelfInductance" Text="self inductance (H)" */
		DatapointSubType_14_63, /*!< Id="DPST-14-63" Number="63" Name="DPT_Value_SolidAngle" Text="solid angle (sr)" */
		DatapointSubType_14_64, /*!< Id="DPST-14-64" Number="64" Name="DPT_Value_Sound_Intensity" Text="sound intensity (W/m)" */
		DatapointSubType_14_65, /*!< Id="DPST-14-65" Number="65" Name="DPT_Value_Speed" Text="speed (m/s)" */
		DatapointSubType_14_66, /*!< Id="DPST-14-66" Number="66" Name="DPT_Value_Stress" Text="stress (Pa)" */
		DatapointSubType_14_67, /*!< Id="DPST-14-67" Number="67" Name="DPT_Value_Surface_Tension" Text="surface tension (N/m)" */
		DatapointSubType_14_68, /*!< Id="DPST-14-68" Number="68" Name="DPT_Value_Common_Temperature" Text="temperature (C)" */
		DatapointSubType_14_69, /*!< Id="DPST-14-69" Number="69" Name="DPT_Value_Absolute_Temperature" Text="temperature absolute (C)" */
		DatapointSubType_14_70, /*!< Id="DPST-14-70" Number="70" Name="DPT_Value_TemperatureDifference" Text="temperature difference (K)" */
		DatapointSubType_14_71, /*!< Id="DPST-14-71" Number="71" Name="DPT_Value_Thermal_Capacity" Text="thermal capacity (J/K)" */
		DatapointSubType_14_72, /*!< Id="DPST-14-72" Number="72" Name="DPT_Value_Thermal_Conductivity" Text="thermal conductivity (W/mK)" */
		DatapointSubType_14_73, /*!< Id="DPST-14-73" Number="73" Name="DPT_Value_ThermoelectricPower" Text="thermoelectric power (V/K)" */
		DatapointSubType_14_74, /*!< Id="DPST-14-74" Number="74" Name="DPT_Value_Time" Text="time (s)" */
		DatapointSubType_14_75, /*!< Id="DPST-14-75" Number="75" Name="DPT_Value_Torque" Text="torque (Nm)" */
		DatapointSubType_14_76, /*!< Id="DPST-14-76" Number="76" Name="DPT_Value_Volume" Text="volume (m)" */
		DatapointSubType_14_77, /*!< Id="DPST-14-77" Number="77" Name="DPT_Value_Volume_Flux" Text="volume flux (m/s)" */
		DatapointSubType_14_78, /*!< Id="DPST-14-78" Number="78" Name="DPT_Value_Weight" Text="weight (N)" */
		DatapointSubType_14_79, /*!< Id="DPST-14-79" Number="79" Name="DPT_Value_Work" Text="work (J)" */

		DatapointType_15, /*!< Id="DPT-15" Number="15" Name="15.xxx" Text="entrance access" SizeInBit="32" */
		DatapointSubType_15_0, /*!< Id="DPST-15-0" Number="0" Name="DPT_Access_Data" Text="entrance access" */

		DatapointType_16, /*!< Id="DPT-16" Number="16" Name="16.xxx" Text="character string" SizeInBit="112" */
		DatapointSubType_16_0, /*!< Id="DPST-16-0" Number="0" Name="DPT_String_ASCII" Text="Character String (ASCII)" */
		DatapointSubType_16_1, /*!< Id="DPST-16-1" Number="1" Name="DPT_String_8859_1" Text="Character String (ISO 8859-1)" */

		DatapointType_17, /*!< Id="DPT-17" Number="17" Name="17.xxx" Text="scene number" SizeInBit="8" */
		DatapointSubType_17_1, /*!< Id="DPST-17-1" Number="1" Name="DPT_SceneNumber" Text="scene number" */

		DatapointType_18, /*!< Id="DPT-18" Number="18" Name="18.xxx" Text="scene control" SizeInBit="8" */
		DatapointSubType_18_1, /*!< Id="DPST-18-1" Number="1" Name="DPT_SceneControl" Text="scene control" */

		DatapointType_19, /*!< Id="DPT-19" Number="19" Name="19.xxx" Text="Date Time" SizeInBit="64" */
		DatapointSubType_19_1, /*!< Id="DPST-19-1" Number="1" Name="DPT_DateTime" Text="date time" */

		DatapointType_20, /*!< Id="DPT-20" Number="20" Name="20.xxx" Text="1-byte" SizeInBit="8" */
		DatapointSubType_20_1, /*!< Id="DPST-20-1" Number="1" Name="DPT_SCLOMode" Text="SCLO mode" */
		DatapointSubType_20_2, /*!< Id="DPST-20-2" Number="2" Name="DPT_BuildingMode" Text="building mode" */
		DatapointSubType_20_3, /*!< Id="DPST-20-3" Number="3" Name="DPT_OccMode" Text="occupied" */
		DatapointSubType_20_4, /*!< Id="DPST-20-4" Number="4" Name="DPT_Priority" Text="priority" */
		DatapointSubType_20_5, /*!< Id="DPST-20-5" Number="5" Name="DPT_LightApplicationMode" Text="light application mode" */
		DatapointSubType_20_6, /*!< Id="DPST-20-6" Number="6" Name="ApplicationArea" Text="light application area" */
		DatapointSubType_20_7, /*!< Id="DPST-20-7" Number="7" Name="DPT_AlarmClassType" Text="alarm class" */
		DatapointSubType_20_8, /*!< Id="DPST-20-8" Number="8" Name="PSUMode" Text="PSU mode" */
		DatapointSubType_20_11, /*!< Id="DPST-20-11" Number="11" Name="DPT_ErrorClass_System" Text="system error class" */
		DatapointSubType_20_12, /*!< Id="DPST-20-12" Number="12" Name="DPT_ErrorClass_HVAC" Text="HVAC error class" */
		DatapointSubType_20_13, /*!< Id="DPST-20-13" Number="13" Name="DPT_Time_Delay" Text="time delay" */
		DatapointSubType_20_14, /*!< Id="DPST-20-14" Number="14" Name="DPT_Beaufort_Wind_Force_Scale" Text="wind force scale (0..12)" */
		DatapointSubType_20_17, /*!< Id="DPST-20-17" Number="17" Name="DPT_SensorSelect" Text="sensor mode" */
		DatapointSubType_20_20, /*!< Id="DPST-20-20" Number="20" Name="DPT_ActuatorConnectType" Text="actuator connect type" */
		DatapointSubType_20_100, /*!< Id="DPST-20-100" Number="100" Name="DPT_FuelType" Text="fuel type" */
		DatapointSubType_20_101, /*!< Id="DPST-20-101" Number="101" Name="DPT_BurnerType" Text="burner type" */
		DatapointSubType_20_102, /*!< Id="DPST-20-102" Number="102" Name="DPT_HVACMode" Text="HVAC mode" */
		DatapointSubType_20_103, /*!< Id="DPST-20-103" Number="103" Name="DPT_DHWMode" Text="DHW mode" */
		DatapointSubType_20_104, /*!< Id="DPST-20-104" Number="104" Name="DPT_LoadPriority" Text="load priority" */
		DatapointSubType_20_105, /*!< Id="DPST-20-105" Number="105" Name="DPT_HVACContrMode" Text="HVAC control mode" */
		DatapointSubType_20_106, /*!< Id="DPST-20-106" Number="106" Name="DPT_HVACEmergMode" Text="HVAC emergency mode" */
		DatapointSubType_20_107, /*!< Id="DPST-20-107" Number="107" Name="DPT_ChangeoverMode" Text="changeover mode" */
		DatapointSubType_20_108, /*!< Id="DPST-20-108" Number="108" Name="DPT_ValveMode" Text="valve mode" */
		DatapointSubType_20_109, /*!< Id="DPST-20-109" Number="109" Name="DPT_DamperMode" Text="damper mode" */
		DatapointSubType_20_110, /*!< Id="DPST-20-110" Number="110" Name="DPT_HeaterMode" Text="heater mode" */
		DatapointSubType_20_111, /*!< Id="DPST-20-111" Number="111" Name="DPT_FanMode" Text="fan mode" */
		DatapointSubType_20_112, /*!< Id="DPST-20-112" Number="112" Name="DPT_MasterSlaveMode" Text="master/slave mode" */
		DatapointSubType_20_113, /*!< Id="DPST-20-113" Number="113" Name="DPT_StatusRoomSetp" Text="status room setpoint" */
		DatapointSubType_20_114, /*!< Id="DPST-20-114" Number="114" Name="DPT_Metering_DeviceType" Text="metering device type" */
		DatapointSubType_20_120, /*!< Id="DPST-20-120" Number="120" Name="DPT_ADAType" Text="ADA type" */
		DatapointSubType_20_121, /*!< Id="DPST-20-121" Number="121" Name="DPT_BackupMode" Text="backup mode" */
		DatapointSubType_20_122, /*!< Id="DPST-20-122" Number="122" Name="DPT_StartSynchronization" Text="start synchronization type" */
		DatapointSubType_20_600, /*!< Id="DPST-20-600" Number="600" Name="DPT_Behaviour_Lock_Unlock" Text="behavior lock/unlock" */
		DatapointSubType_20_601, /*!< Id="DPST-20-601" Number="601" Name="DPT_Behaviour_Bus_Power_Up_Down" Text="behavior bus power up/down" */
		DatapointSubType_20_602, /*!< Id="DPST-20-602" Number="602" Name="DPT_DALI_Fade_Time" Text="dali fade time" */
		DatapointSubType_20_603, /*!< Id="DPST-20-603" Number="603" Name="DPT_BlinkingMode" Text="blink mode" */
		DatapointSubType_20_604, /*!< Id="DPST-20-604" Number="604" Name="DPT_LightControlMode" Text="light control mode" */
		DatapointSubType_20_605, /*!< Id="DPST-20-605" Number="605" Name="DPT_SwitchPBModel" Text="PB switch mode" */
		DatapointSubType_20_606, /*!< Id="DPST-20-606" Number="606" Name="DPT_PBAction" Text="PB action mode" */
		DatapointSubType_20_607, /*!< Id="DPST-20-607" Number="607" Name="DPT_DimmPBModel" Text="PB dimm mode" */
		DatapointSubType_20_608, /*!< Id="DPST-20-608" Number="608" Name="DPT_SwitchOnMode" Text="switch on mode" */
		DatapointSubType_20_609, /*!< Id="DPST-20-609" Number="609" Name="DPT_LoadTypeSet" Text="load type" */
		DatapointSubType_20_610, /*!< Id="DPST-20-610" Number="610" Name="DPT_LoadTypeDetected" Text="load type detection" */
		DatapointSubType_20_801, /*!< Id="DPST-20-801" Number="801" Name="DPT_SABExcept-Behaviour" Text="SAB except behavior" */
		DatapointSubType_20_802, /*!< Id="DPST-20-802" Number="802" Name="DPT_SABBehaviour_Lock_Unlock" Text="SAB behavior on lock/unlock" */
		DatapointSubType_20_803, /*!< Id="DPST-20-803" Number="803" Name="DPT_SSSBMode" Text="SSSB mode" */
		DatapointSubType_20_804, /*!< Id="DPST-20-804" Number="804" Name="DPT_BlindsControlMode" Text="blinds control mode" */
		DatapointSubType_20_1000, /*!< Id="DPST-20-1000" Number="1000" Name="DPT_CommMode" Text="communication mode" */
		DatapointSubType_20_1001, /*!< Id="DPST-20-1001" Number="1001" Name="DPT_AddInfoTypes" Text="additional information type" */
		DatapointSubType_20_1002, /*!< Id="DPST-20-1002" Number="1002" Name="DPT_RF_ModeSelect" Text="RF mode selection" */
		DatapointSubType_20_1003, /*!< Id="DPST-20-1003" Number="1003" Name="DPT_RF_FilterSelect" Text="RF filter mode selection" */

		DatapointType_21, /*!< Id="DPT-21" Number="21" Name="21.xxx" Text="8-bit set" SizeInBit="8" */
		DatapointSubType_21_1, /*!< Id="DPST-21-1" Number="1" Name="DPT_StatusGen" Text="general status" */
		DatapointSubType_21_2, /*!< Id="DPST-21-2" Number="2" Name="DPT_Device_Control" Text="device control" */
		DatapointSubType_21_100, /*!< Id="DPST-21-100" Number="100" Name="DPT_ForceSign" Text="forcing signal" */
		DatapointSubType_21_101, /*!< Id="DPST-21-101" Number="101" Name="DPT_ForceSignCool" Text="forcing signal cool" */
		DatapointSubType_21_102, /*!< Id="DPST-21-102" Number="102" Name="DPT_StatusRHC" Text="room heating controller status" */
		DatapointSubType_21_103, /*!< Id="DPST-21-103" Number="103" Name="DPT_StatusSDHWC" Text="solar DHW controller status" */
		DatapointSubType_21_104, /*!< Id="DPST-21-104" Number="104" Name="DPT_FuelTypeSet" Text="fuel type set" */
		DatapointSubType_21_105, /*!< Id="DPST-21-105" Number="105" Name="DPT_StatusRCC" Text="room cooling controller status" */
		DatapointSubType_21_106, /*!< Id="DPST-21-106" Number="106" Name="DPT_StatusAHU" Text="ventilation controller status" */
		DatapointSubType_21_601, /*!< Id="DPST-21-601" Number="601" Name="DPT_LightActuatorErrorInfo" Text="lighting actuator error information" */
		DatapointSubType_21_1000, /*!< Id="DPST-21-1000" Number="1000" Name="DPT_RF_ModeInfo" Text="RF communication mode info" */
		DatapointSubType_21_1001, /*!< Id="DPST-21-1001" Number="1001" Name="DPT_RF_FilterInfo" Text="cEMI server supported RF filtering modes" */
		DatapointSubType_21_1010, /*!< Id="DPST-21-1010" Number="1010" Name="DPT_Channel_Activation_8" Text="channel activation for 8 channels" */

		DatapointType_22, /*!< Id="DPT-22" Number="22" Name="22.xxx" Text="16-bit set" SizeInBit="16" */
		DatapointSubType_22_100, /*!< Id="DPST-22-100" Number="100" Name="DPT_StatusDHWC" Text="DHW controller status" */
		DatapointSubType_22_101, /*!< Id="DPST-22-101" Number="101" Name="DPT_StatusRHCC" Text="RHCC status" */
		DatapointSubType_22_1000, /*!< Id="DPST-22-1000" Number="1000" Name="DPT_Media" Text="media" */
		DatapointSubType_22_1010, /*!< Id="DPST-22-1010" Number="1010" Name="DPT_Channel_Activation_16" Text="channel activation for 16 channels" */

		DatapointType_23, /*!< Id="DPT-23" Number="23" Name="23.xxx" Text="2-bit set" SizeInBit="2" */
		DatapointSubType_23_1, /*!< Id="DPST-23-1" Number="1" Name="DPT_OnOffAction" Text="on/off action" */
		DatapointSubType_23_2, /*!< Id="DPST-23-2" Number="2" Name="DPT_Alarm_Reaction" Text="alarm reaction" */
		DatapointSubType_23_3, /*!< Id="DPST-23-3" Number="3" Name="DPT_UpDown_Action" Text="up/down action" */
		DatapointSubType_23_102, /*!< Id="DPST-23-102" Number="102" Name="DPT_HVAC_PB_Action" Text="HVAC push button action" */

		DatapointType_25, /*!< Id="DPT-25" Number="25" Name="25.xxx" Text="2-nibble set" SizeInBit="8" */
		DatapointSubType_25_1000, /*!< Id="DPST-25-1000" Number="1000" Name="DPT_DoubleNibble" Text="busy/nak repetitions" */

		DatapointType_26, /*!< Id="DPT-26" Number="26" Name="26.xxx" Text="8-bit set" SizeInBit="8" */
		DatapointSubType_26_1, /*!< Id="DPST-26-1" Number="1" Name="DPT_SceneInfo" Text="scene information" */

		DatapointType_27, /*!< Id="DPT-27" Number="27" Name="27.xxx" Text="32-bit set" SizeInBit="32" */
		DatapointSubType_27_1, /*!< Id="DPST-27-1" Number="1" Name="DPT_CombinedInfoOnOff" Text="bit-combined info on/off" */

		DatapointType_29, /*!< Id="DPT-29" Number="29" Name="29.xxx" Text="electrical energy" SizeInBit="64" */
		DatapointSubType_29_10, /*!< Id="DPST-29-10" Number="10" Name="DPT_ActiveEnergy_V64" Text="active energy (Wh)" */
		DatapointSubType_29_11, /*!< Id="DPST-29-11" Number="11" Name="DPT_ApparantEnergy_V64" Text="apparent energy (VAh)" */
		DatapointSubType_29_12, /*!< Id="DPST-29-12" Number="12" Name="DPT_ReactiveEnergy_V64" Text="reactive energy (VARh)" */

		DatapointType_30, /*!< Id="DPT-30" Number="30" Name="30.xxx" Text="24 times channel activation" SizeInBit="24" */
		DatapointSubType_30_1010, /*!< Id="DPST-30-1010" Number="1010" Name="DPT_Channel_Activation_24" Text="activation state 0..23" */

		DatapointType_206, /*!< Id="DPT-206" Number="206" Name="206.xxx" Text="16-bit unsigned value & 8-bit enum" SizeInBit="24" */
		DatapointSubType_206_100, /*!< Id="DPST-206-100" Number="100" Name="DPT_HVACModeNext" Text="time delay & HVAC mode" */
		DatapointSubType_206_102, /*!< Id="DPST-206-102" Number="102" Name="DPT_DHWModeNext" Text="time delay & DHW mode" */
		DatapointSubType_206_104, /*!< Id="DPST-206-104" Number="104" Name="DPT_OccModeNext" Text="time delay & occupancy mode" */
		DatapointSubType_206_105, /*!< Id="DPST-206-105" Number="105" Name="DPT_BuildingModeNext" Text="time delay & building mode" */

		DatapointType_217, /*!< Id="DPT-217" Number="217" Name="217.xxx" Text="datapoint type version" SizeInBit="16" */
		DatapointSubType_217_1, /*!< Id="DPST-217-1" Number="1" Name="DPT_Version" Text="DPT version" */

		DatapointType_219, /*!< Id="DPT-219" Number="219" Name="219.xxx" Text="alarm info" SizeInBit="48" */
		DatapointSubType_219_1, /*!< Id="DPST-219-1" Number="1" Name="DPT_AlarmInfo" Text="alarm info" */

		DatapointType_222, /*!< Id="DPT-222" Number="222" Name="222.xxx" Text="3x 2-byte float value" SizeInBit="48" */
		DatapointSubType_222_100, /*!< Id="DPST-222-100" Number="100" Name="DPT_TempRoomSetpSetF16[3]" Text="room temperature setpoint" */
		DatapointSubType_222_101, /*!< Id="DPST-222-101" Number="101" Name="DPT_TempRoomSetpSetShiftF16[3]" Text="room temperature setpoint shift" */

		DatapointType_229, /*!< Id="DPT-229" Number="229" Name="229.xxx" Text="4-1-1 byte combined information" SizeInBit="48" */
		DatapointSubType_229_1, /*!< Id="DPST-229-1" Number="1" Name="DPT_MeteringValue" Text="metering value (value,encoding,cmd)" */

		DatapointType_230, /*!< Id="DPT-230" Number="230" Name="230.xxx" Text="MBus address" SizeInBit="64" */
		DatapointSubType_230_1000, /*!< Id="DPST-230-1000" Number="1000" Name="DPT_MBus_Address" Text="MBus address" */

		DatapointType_232, /*!< Id="DPT-232" Number="232" Name="232.xxx" Text="3-byte colour RGB" SizeInBit="24" */
		DatapointSubType_232_600, /*!< Id="DPST-232-600" Number="600" Name="DPT_Colour_RGB" Text="RGB value 3x(0..255)" */

		DatapointType_234, /*!< Id="DPT-234" Number="234" Name="234.xxx" Text="language code ISO 639-1" SizeInBit="16" */
		DatapointSubType_234_1, /*!< Id="DPST-234-1" Number="1" Name="DPT_LanguageCodeAlpha2_ASCII" Text="language code (ASCII)" */

		DatapointType_237, /*!< Id="DPT-237" Number="237" Name="237.xxx" Text="configuration/ diagnostics" SizeInBit="16" */
		DatapointSubType_237_600, /*!< Id="DPST-237-600" Number="600" Name="DPT_DALI_Control_Gear_Diagnostic" Text="diagnostic value" */

		DatapointType_238, /*!< Id="DPT-238" Number="238" Name="238.xxx" Text="configuration/ diagnostics" SizeInBit="8" */
		DatapointSubType_238_600, /*!< Id="DPST-238-600" Number="600" Name="DPT_DALI_Diagnostics" Text="diagnostic value" */

	};

	static int getTypeFromId(const std::string& datapointId);
};

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_DEFINES_DATAPOINT_TYPES_H__
