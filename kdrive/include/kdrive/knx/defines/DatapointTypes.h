//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
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
	    DatapointType_1,			/*!< Id="DPT-1" Number="1" Name="1 bit" Text="1 bit" SizeInBit="1" */
	    DatapointSubType_1_1,		/*!< Id="DPST-1-1" Number="1" Name="DPT_Switch" Text="on/off" */
	    DatapointSubType_1_2,		/*!< Id="DPST-1-2" Number="2" Name="DPT_Bool" Text="boolean" */
	    DatapointSubType_1_3,		/*!< Id="DPST-1-3" Number="3" Name="DPT_Enable" Text="enable" */
	    DatapointSubType_1_4,		/*!< Id="DPST-1-4" Number="4" Name="DPT_Ramp" Text="ramp" */
	    DatapointSubType_1_5,		/*!< Id="DPST-1-5" Number="5" Name="DPT_Alarm" Text="alarm" */
	    DatapointSubType_1_6,		/*!< Id="DPST-1-6" Number="6" Name="DPT_BinaryValue" Text="binary value" */
	    DatapointSubType_1_7,		/*!< Id="DPST-1-7" Number="7" Name="DPT_Step" Text="step" */
	    DatapointSubType_1_8,		/*!< Id="DPST-1-8" Number="8" Name="DPT_UpDown" Text="up/down" */
	    DatapointSubType_1_9,		/*!< Id="DPST-1-9" Number="9" Name="DPT_OpenClose" Text="open/close" */
	    DatapointSubType_1_10,		/*!< Id="DPST-1-10" Number="10" Name="DPT_Start" Text="start/stop" */
	    DatapointSubType_1_11,		/*!< Id="DPST-1-11" Number="11" Name="DPT_State" Text="state" */
	    DatapointSubType_1_12,		/*!< Id="DPST-1-12" Number="12" Name="DPT_Invert" Text="invert" */
	    DatapointSubType_1_15,		/*!< Id="DPST-1-15" Number="15" Name="DPT_Reset" Text="reset" */
	    DatapointSubType_1_16,		/*!< Id="DPST-1-16" Number="16" Name="DPT_Ack" Text="acknowledge" */
	    DatapointSubType_1_17,		/*!< Id="DPST-1-17" Number="17" Name="DPT_Trigger" Text="trigger" */
	    DatapointSubType_1_18,		/*!< Id="DPST-1-18" Number="18" Name="DPT_Occupancy" Text="occupied" */
	    DatapointSubType_1_19,		/*!< Id="DPST-1-19" Number="19" Name="DPT_Window_Door" Text="open window" */
	    DatapointSubType_1_21,		/*!< Id="DPST-1-21" Number="21" Name="DPT_LogicalFunction" Text="and/or" */
	    DatapointSubType_1_22,		/*!< Id="DPST-1-22" Number="22" Name="DPT_Scene_AB" Text="scene A/B" */
	    DatapointSubtype_1_100,     /*!< Id="DPST-1-100" Number="100" Name="DPT_Heat_Cool" Text="cooling/heating" */

	    DatapointType_2,			/*!< Id="DPT-2" Number="2" Name="1 bit controlled" Text="1 bit controlled" SizeInBit="2" */
	    DatapointSubType_2_1,		/*!< Id="DPST-2-1" Number="1" Name="DPT_Switch_Control" Text="switch control" */
	    DatapointSubType_2_2,		/*!< Id="DPST-2-2" Number="2" Name="DPT_Bool_Control" Text="boolean control" */
	    DatapointSubType_2_3,		/*!< Id="DPST-2-3" Number="3" Name="DPT_Enable_Control" Text="enable control" */
	    DatapointSubType_2_4,		/*!< Id="DPST-2-4" Number="4" Name="DPT_Ramp_Control" Text="ramp control" */
	    DatapointSubType_2_5,		/*!< Id="DPST-2-5" Number="5" Name="DPT_Alarm_Control" Text="alarm control" */
	    DatapointSubType_2_6,		/*!< Id="DPST-2-6" Number="6" Name="DPT_BinaryValue_Control" Text="binary value control" */
	    DatapointSubType_2_7,		/*!< Id="DPST-2-7" Number="7" Name="DPT_Step_Control" Text="step control" */
	    DatapointSubType_2_10,		/*!< Id="DPST-2-10" Number="10" Name="DPT_Start_Control" Text="start control" */
	    DatapointSubType_2_11,		/*!< Id="DPST-2-11" Number="11" Name="DPT_State_Control" Text="state control" */
	    DatapointSubType_2_12,		/*!< Id="DPST-2-12" Number="12" Name="DPT_Invert_Control" Text="invert control" */

	    DatapointType_3,			/*!< Id="DPT-3" Number="3" Name="3 bit controlled" Text="3 bit controlled" SizeInBit="4"  */
	    DatapointSubType_3_7,		/*!< Id="DPST-3-7" Number="7" Name="DPT_Control_Dimming" Text="dimming control" */
	    DatapointSubType_3_8,		/*!< Id="DPST-3-8" Number="8" Name="DPT_Control_Blinds" Text="blind control" */

	    DatapointType_4,			/*!< Id="DPT-4" Number="4" Name="Character" Text="Character" SizeInBit="8" */
	    DatapointSubType_4_1,		/*!< Id="DPST-4-1" Number="1" Name="DPT_Char_ASCII" Text="character (ASCII)" */
	    DatapointSubType_4_2,		/*!< Id="DPST-4-2" Number="2" Name="DPT_Char_8859_1" Text="character (ISO 8859-1)" */

	    DatapointType_5,			/*!< Id="DPT-5" Number="5" Name="8 bit unsigned value" Text="8 bit unsigned value" SizeInBit="8" */
	    DatapointSubType_5_1,		/*!< Id="DPST-5-1" Number="1" Name="DPT_Scaling" Text="percentage (0..100%)" */
	    DatapointSubType_5_3,		/*!< Id="DPST-5-3" Number="3" Name="DPT_Angle" Text="angle (degrees)" */
	    DatapointSubType_5_4,		/*!< Id="DPST-5-4" Number="4" Name="DPT_Percent_U8" Text="percentage (0..255%)" */
	    DatapointSubType_5_10,		/*!< Id="DPST-5-10" Number="10" Name="DPT_Value_1_Ucount" Text="counter pulses (0..255)" */

	    DatapointType_6,			/*!< Id="DPT-6" Number="6" Name="8 bit signed value" Text="8 bit signed value" SizeInBit="8" */
	    DatapointSubType_6_1,		/*!< Id="DPST-6-1" Number="1" Name="DPT_Percent_V8" Text="percentage (-128..127%)" */
	    DatapointSubType_6_10,		/*!< Id="DPST-6-10" Number="10" Name="DPT_Value_1_Count" Text="counter pulses (-128..127)" */

	    DatapointType_7,			/*!< Id="DPT-7" Number="7" Name="2 byte unsigned value" Text="2 byte unsigned value" SizeInBit="16" */
	    DatapointSubType_7_1,		/*!< Id="DPST-7-1" Number="1" Name="DPT_Value_2_Ucount" Text="pulses" */
	    DatapointSubType_7_2,		/*!< Id="DPST-7-2" Number="2" Name="DPT_TimePeriodMsec" Text="time (ms)" */
	    DatapointSubType_7_3,		/*!< Id="DPST-7-3" Number="3" Name="DPT_TimePeriod10Msec" Text="time (10 ms)" */
	    DatapointSubType_7_4,		/*!< Id="DPST-7-4" Number="4" Name="DPT_TimePeriod100Msec" Text="time (100 ms)" */
	    DatapointSubType_7_5,		/*!< Id="DPST-7-5" Number="5" Name="DPT_TimePeriodSec" Text="time (s)" */
	    DatapointSubType_7_6,		/*!< Id="DPST-7-6" Number="6" Name="DPT_TimePeriodMin" Text="time (min)" */
	    DatapointSubType_7_7,		/*!< Id="DPST-7-7" Number="7" Name="DPT_TimePeriodHrs" Text="time (h)" */

	    DatapointType_8,			/*!< Id="DPT-8" Number="8" Name="2 byte signed value" Text="2 byte signed value" SizeInBit="16" */
	    DatapointSubType_8_1,		/*!< Id="DPST-8-1" Number="1" Name="DPT_Value_2_Count" Text="pulses difference" */
	    DatapointSubType_8_2,		/*!< Id="DPST-8-2" Number="2" Name="DPT_DeltaTimeMsec" Text="time lag (ms)" */
	    DatapointSubType_8_3,		/*!< Id="DPST-8-3" Number="3" Name="DPT_DeltaTime10Msec" Text="time lag(10 ms)" */
	    DatapointSubType_8_4,		/*!< Id="DPST-8-4" Number="4" Name="DPT_DeltaTime100Msec" Text="time lag (100 ms)" */
	    DatapointSubType_8_5,		/*!< Id="DPST-8-5" Number="5" Name="DPT_DeltaTimeSec" Text="time lag (s)" */
	    DatapointSubType_8_6,		/*!< Id="DPST-8-6" Number="6" Name="DPT_DeltaTimeMin" Text="time lag (min)" */
	    DatapointSubType_8_7,		/*!< Id="DPST-8-7" Number="7" Name="DPT_DeltaTimeHrs" Text="time lag (h)" */
	    DatapointSubType_8_10,		/*!< Id="DPST-8-10" Number="10" Name="DPT_Percent_V16" Text="percentage difference (%)" */

	    DatapointType_9,			/*!< Id="DPT-9" Number="9" Name="2 byte float value" Text="2 byte float value" SizeInBit="16" */
	    DatapointSubType_9_1,		/*!< Id="DPST-9-1" Number="1" Name="DPT_Value_Temp" Text="temperature (C)" */
	    DatapointSubType_9_2,		/*!< Id="DPST-9-2" Number="2" Name="DPT_Value_Tempd" Text="temperature difference (K)" */
	    DatapointSubType_9_3,		/*!< Id="DPST-9-3" Number="3" Name="DPT_Value_Tempa" Text="kelvin/hour (K/h)" */
	    DatapointSubType_9_4,		/*!< Id="DPST-9-4" Number="4" Name="DPT_Value_Lux" Text="lux (Lux)" */
	    DatapointSubType_9_5,		/*!< Id="DPST-9-5" Number="5" Name="DPT_Value_Wsp" Text="speed (m/s)" */
	    DatapointSubType_9_6,		/*!< Id="DPST-9-6" Number="6" Name="DPT_Value_Pres" Text="pressure (Pa)" */
	    DatapointSubType_9_7,		/*!< Id="DPST-9-7" Number="7" Name="DPT_Value_Humidity" Text="percentage (%)" */
	    DatapointSubType_9_8,		/*!< Id="DPST-9-8" Number="8" Name="DPT_Value_AirQuality" Text="parts/million (ppm)" */
	    DatapointSubType_9_10,		/*!< Id="DPST-9-10" Number="10" Name="DPT_Value_Time1" Text="time (s)" */
	    DatapointSubType_9_11,		/*!< Id="DPST-9-11" Number="11" Name="DPT_Value_Time2" Text="time (ms)" */
	    DatapointSubType_9_20,		/*!< Id="DPST-9-20" Number="20" Name="DPT_Value_Volt" Text="voltage (mV)" */
	    DatapointSubType_9_21,		/*!< Id="DPST-9-21" Number="21" Name="DPT_Value_Curr" Text="cuurent (mA)" */
	    DatapointSubType_9_22,		/*!< Id="DPST-9-22" Number="22" Name="DPT_PowerDensity" Text="power denisity (W/m2)" */
	    DatapointSubType_9_23,		/*!< Id="DPST-9-23" Number="23" Name="DPT_KelvinPerPercent" Text="kelvin/percent (K/%)" */
	    DatapointSubType_9_24,		/*!< Id="DPST-9-24" Number="24" Name="DPT_Power" Text="power (kW)" */
	    DatapointSubType_9_25,		/*!< Id="DPST-9-25" Number="25" Name="DPT_Value_Volume_Flow" Text="litre/hour (l/h)" */

	    DatapointType_10,			/*!< Id="DPT-10" Number="10" Name="Time" Text="Time" SizeInBit="24" */
	    DatapointSubType_10_1,		/*!< Id="DPST-10-1" Number="1" Name="DPT_TimeOfDay" Text="time of day" */

	    DatapointType_11,			/*!< Id="DPT-11" Number="11" Name="Date" Text="Date" SizeInBit="24" */
	    DatapointSubType_11_1,		/*!< Id="DPST-11-1" Number="1" Name="DPT_Date" Text="date" */

	    DatapointType_12,			/*!< Id="DPT-12" Number="12" Name="4 byte unsigned value" Text="4 byte unsigned value" SizeInBit="32" */
	    DatapointSubType_12_1,		/*!< Id="DPST-12-1" Number="1" Name="DPT_Value_4_Ucount" Text="counter pulses (unsigned)" */

	    DatapointType_13,			/*!< Id="DPT-13" Number="13" Name="4 byte signed value" Text="4 byte signed value" SizeInBit="32" */
	    DatapointSubType_13_1,		/*!< Id="DPST-13-1" Number="1" Name="DPT_Value_4_Count" Text="counter pulses (signed)" */
	    DatapointSubType_13_100,	/*!< Id="DPST-13-100" Number="100" Name="DPT_LongDeltaTimeSec" Text="time lag (s)" */

	    DatapointType_14,			/*!< Id="DPT-14" Number="14" Name="4 byte float value" Text="4 byte float value" SizeInBit="32" */
	    DatapointSubType_14_0,		/*!< Id="DPST-14-0" Number="0" Name="DPT_Value_Acceleration" Text="acceleration (m/s2)" */
	    DatapointSubType_14_1,		/*!< Id="DPST-14-1" Number="1" Name="DPT_Value_Acceleration_Angular" Text="angular acceleration (rad/s2)" */
	    DatapointSubType_14_2,		/*!< Id="DPST-14-2" Number="2" Name="DPT_Value_Activation_Energy" Text="activation energy (J/mol)" */
	    DatapointSubType_14_3,		/*!< Id="DPST-14-3" Number="3" Name="DPT_Value_Activity" Text="radioactive activity (1/s)" */
	    DatapointSubType_14_4,		/*!< Id="DPST-14-4" Number="4" Name="DPT_Value_Mol" Text="amount of substance (mol)" */
	    DatapointSubType_14_5,		/*!< Id="DPST-14-5" Number="5" Name="DPT_Value_Amplitude" Text="amplitude" */
	    DatapointSubType_14_6,		/*!< Id="DPST-14-6" Number="6" Name="DPT_Value_AngleRad" Text="angle (radiant)" */
	    DatapointSubType_14_7,		/*!< Id="DPST-14-7" Number="7" Name="DPT_Value_AngleDeg" Text="angle (degree)" */
	    DatapointSubType_14_8,		/*!< Id="DPST-14-8" Number="8" Name="DPT_Value_Angular_Momentum" Text="angular momentum (Js)" */
	    DatapointSubType_14_9,		/*!< Id="DPST-14-9" Number="9" Name="DPT_Value_Angular_Velocity" Text="angular velocity (rad/s)" */
	    DatapointSubType_14_10,		/*!< Id="DPST-14-10" Number="10" Name="DPT_Value_Area" Text="area (m*m)" */
	    DatapointSubType_14_11,		/*!< Id="DPST-14-11" Number="11" Name="DPT_Value_Capacitance" Text="capacitance (F)" */
	    DatapointSubType_14_12,		/*!< Id="DPST-14-12" Number="12" Name="DPT_Value_Charge_DensitySurface" Text="flux density (C/m2)" */
	    DatapointSubType_14_13,		/*!< Id="DPST-14-13" Number="13" Name="DPT_Value_Charge_DensityVolume" Text="charge density (C/m3)" */
	    DatapointSubType_14_14,		/*!< Id="DPST-14-14" Number="14" Name="DPT_Value_Compressibility" Text="compressibility (m2/N)" */
	    DatapointSubType_14_15,		/*!< Id="DPST-14-15" Number="15" Name="DPT_Value_Conductance" Text="conductance (S)" */
	    DatapointSubType_14_16,		/*!< Id="DPST-14-16" Number="16" Name="DPT_Value_Electrical_Conductivity" Text="conductivity  (S/m)" */
	    DatapointSubType_14_17,		/*!< Id="DPST-14-17" Number="17" Name="DPT_Value_Density" Text="density (kg/m3)" */
	    DatapointSubType_14_18,		/*!< Id="DPST-14-18" Number="18" Name="DPT_Value_Electric_Charge" Text="electric charge (C)" */
	    DatapointSubType_14_19,		/*!< Id="DPST-14-19" Number="19" Name="DPT_Value_Electric_Current" Text="electric current (A)" */
	    DatapointSubType_14_20,		/*!< Id="DPST-14-20" Number="20" Name="DPT_Value_Electric_CurrentDensity" Text="electric current density (A/m2)" */
	    DatapointSubType_14_21,		/*!< Id="DPST-14-21" Number="21" Name="DPT_Value_Electric_DipoleMoment" Text="electric dipole moment (Cm)" */
	    DatapointSubType_14_22,		/*!< Id="DPST-14-22" Number="22" Name="DPT_Value_Electric_Displacement" Text="electric displacement (C/m2)" */
	    DatapointSubType_14_23,		/*!< Id="DPST-14-23" Number="23" Name="DPT_Value_Electric_FieldStrength" Text="electric field strength (V/m)" */
	    DatapointSubType_14_24,		/*!< Id="DPST-14-24" Number="24" Name="DPT_Value_Electric_Flux" Text="electric flux (C)" */
	    DatapointSubType_14_25,		/*!< Id="DPST-14-25" Number="25" Name="DPT_Value_Electric_FluxDensity" Text="electric flux density (C/m2)" */
	    DatapointSubType_14_26,		/*!< Id="DPST-14-26" Number="26" Name="DPT_Value_Electric_Polarization" Text="electric polarization (C/m2)" */
	    DatapointSubType_14_27,		/*!< Id="DPST-14-27" Number="27" Name="DPT_Value_Electric_Potential" Text="electric potential (V)" */
	    DatapointSubType_14_28,		/*!< Id="DPST-14-28" Number="28" Name="DPT_Value_Electric_PotentialDifference" Text="electric potential difference (V)" */
	    DatapointSubType_14_29,		/*!< Id="DPST-14-29" Number="29" Name="DPT_Value_ElectromagneticMoment" Text="electromagnetic moment (Am2)" */
	    DatapointSubType_14_30,		/*!< Id="DPST-14-30" Number="30" Name="DPT_Value_Electromotive_Force" Text="electromotive force (V)" */
	    DatapointSubType_14_31,		/*!< Id="DPST-14-31" Number="31" Name="DPT_Value_Energy" Text="energy (J)" */
	    DatapointSubType_14_32,		/*!< Id="DPST-14-32" Number="32" Name="DPT_Value_Force" Text="force (N)" */
	    DatapointSubType_14_33,		/*!< Id="DPST-14-33" Number="33" Name="DPT_Value_Frequency" Text="frequency (Hz)" */
	    DatapointSubType_14_34,		/*!< Id="DPST-14-34" Number="34" Name="DPT_Value_Angular_Frequency" Text="angular frequency (rad/s)" */
	    DatapointSubType_14_35,		/*!< Id="DPST-14-35" Number="35" Name="DPT_Value_Heat_Capacity" Text="heat capacity (J/K)" */
	    DatapointSubType_14_36,		/*!< Id="DPST-14-36" Number="36" Name="DPT_Value_Heat_FlowRate" Text="heat flow rate (W)" */
	    DatapointSubType_14_37,		/*!< Id="DPST-14-37" Number="37" Name="DPT_Value_Heat_Quantity" Text="heat quantity" */
	    DatapointSubType_14_38,		/*!< Id="DPST-14-38" Number="38" Name="DPT_Value_Impedance" Text="impedance (Ohm)" */
	    DatapointSubType_14_39,		/*!< Id="DPST-14-39" Number="39" Name="DPT_Value_Length" Text="length (m)" */
	    DatapointSubType_14_40,		/*!< Id="DPST-14-40" Number="40" Name="DPT_Value_Light_Quantity" Text="light quantity (J)" */
	    DatapointSubType_14_41,		/*!< Id="DPST-14-41" Number="41" Name="DPT_Value_Luminance" Text="luminance (cd/m2)" */
	    DatapointSubType_14_42,		/*!< Id="DPST-14-42" Number="42" Name="DPT_Value_Luminous_Flux" Text="luminous flux (lm)" */
	    DatapointSubType_14_43,		/*!< Id="DPST-14-43" Number="43" Name="DPT_Value_Luminous_Intensity" Text="luminous intensity (cd)" */
	    DatapointSubType_14_44,		/*!< Id="DPST-14-44" Number="44" Name="DPT_Value_Magnetic_FieldStrength" Text="magnetic field strength (A/m)" */
	    DatapointSubType_14_45,		/*!< Id="DPST-14-45" Number="45" Name="DPT_Value_Magnetic_Flux" Text="magnetic flux (Wb)" */
	    DatapointSubType_14_46,		/*!< Id="DPST-14-46" Number="46" Name="DPT_Value_Magnetic_FluxDensity" Text="magnetic flux density (T)" */
	    DatapointSubType_14_47,		/*!< Id="DPST-14-47" Number="47" Name="DPT_Value_Magnetic_Moment" Text="magnetic moment (Am2)" */
	    DatapointSubType_14_48,		/*!< Id="DPST-14-48" Number="48" Name="DPT_Value_Magnetic_Polarization" Text="magnetic polarization (T)" */
	    DatapointSubType_14_49,		/*!< Id="DPST-14-49" Number="49" Name="DPT_Value_Magnetization" Text="magnetization (A/m)" */
	    DatapointSubType_14_50,		/*!< Id="DPST-14-50" Number="50" Name="DPT_Value_MagnetomotiveForce" Text="magnetomotive force (A)" */
	    DatapointSubType_14_51,		/*!< Id="DPST-14-51" Number="51" Name="DPT_Value_Mass" Text="mass (kg)" */
	    DatapointSubType_14_52,		/*!< Id="DPST-14-52" Number="52" Name="DPT_Value_MassFlux" Text="mass flux (kg/s)" */
	    DatapointSubType_14_53,		/*!< Id="DPST-14-53" Number="53" Name="DPT_Value_Momentum" Text="momentum (N/s)" */
	    DatapointSubType_14_54,		/*!< Id="DPST-14-54" Number="54" Name="DPT_Value_Phase_AngleRad" Text="phase angle (rad)" */
	    DatapointSubType_14_55,		/*!< Id="DPST-14-55" Number="55" Name="DPT_Value_Phase_AngleDeg" Text="phase angle ()" */
	    DatapointSubType_14_56,		/*!< Id="DPST-14-56" Number="56" Name="DPT_Value_Power" Text="power (W)" */
	    DatapointSubType_14_57,		/*!< Id="DPST-14-57" Number="57" Name="DPT_Value_Power_Factor" Text="power factor (cos )" */
	    DatapointSubType_14_58,		/*!< Id="DPST-14-58" Number="58" Name="DPT_Value_Pressure" Text="pressure (Pa)" */
	    DatapointSubType_14_59,		/*!< Id="DPST-14-59" Number="59" Name="DPT_Value_Reactance" Text="reactance (Ohm)" */
	    DatapointSubType_14_60,		/*!< Id="DPST-14-60" Number="60" Name="DPT_Value_Resistance" Text="resistance (Ohm)" */
	    DatapointSubType_14_61,		/*!< Id="DPST-14-61" Number="61" Name="DPT_Value_Resistivity" Text="resistivity (Ohmm)" */
	    DatapointSubType_14_62,		/*!< Id="DPST-14-62" Number="62" Name="DPT_Value_SelfInductance" Text="self inductance (H)" */
	    DatapointSubType_14_63,		/*!< Id="DPST-14-63" Number="63" Name="DPT_Value_SolidAngle" Text="solid angle (sr)" */
	    DatapointSubType_14_64,		/*!< Id="DPST-14-64" Number="64" Name="DPT_Value_Sound_Intensity" Text="sound intensity (W/m2)" */
	    DatapointSubType_14_65,		/*!< Id="DPST-14-65" Number="65" Name="DPT_Value_Speed" Text="speed (m/s)" */
	    DatapointSubType_14_66,		/*!< Id="DPST-14-66" Number="66" Name="DPT_Value_Stress" Text="stress (Pa)" */
	    DatapointSubType_14_67,		/*!< Id="DPST-14-67" Number="67" Name="DPT_Value_Surface_Tension" Text="surface tension (N/m)" */
	    DatapointSubType_14_68,		/*!< Id="DPST-14-68" Number="68" Name="DPT_Value_Common_Temperature" Text="temperature (C)" */
	    DatapointSubType_14_69,		/*!< Id="DPST-14-69" Number="69" Name="DPT_Value_Absolute_Temperature" Text="temperature absolute (C)" */
	    DatapointSubType_14_70,		/*!< Id="DPST-14-70" Number="70" Name="DPT_Value_TemperatureDifference" Text="temperature difference (K)" */
	    DatapointSubType_14_71,		/*!< Id="DPST-14-71" Number="71" Name="DPT_Value_Thermal_Capacity" Text="thermal capacity (J/K)" */
	    DatapointSubType_14_72,		/*!< Id="DPST-14-72" Number="72" Name="DPT_Value_Thermal_Conductivity" Text="thermal conductivity (W/mK)" */
	    DatapointSubType_14_73,		/*!< Id="DPST-14-73" Number="73" Name="DPT_Value_ThermoelectricPower" Text="thermoelectric power (V/K)" */
	    DatapointSubType_14_74,		/*!< Id="DPST-14-74" Number="74" Name="DPT_Value_Time" Text="time (s)" */
	    DatapointSubType_14_75,		/*!< Id="DPST-14-75" Number="75" Name="DPT_Value_Torque" Text="torque (Nm)" */
	    DatapointSubType_14_76,		/*!< Id="DPST-14-76" Number="76" Name="DPT_Value_Volume" Text="volume (m3)" */
	    DatapointSubType_14_77,		/*!< Id="DPST-14-77" Number="77" Name="DPT_Value_Volume_Flux" Text="volume flux (m3/s)" */
	    DatapointSubType_14_78,		/*!< Id="DPST-14-78" Number="78" Name="DPT_Value_Weight" Text="weight (N)" */
	    DatapointSubType_14_79,		/*!< Id="DPST-14-79" Number="79" Name="DPT_Value_Work" Text="work (J)" */

	    DatapointType_15,			/*!< Id="DPT-15" Number="15" Name="Entrance access" Text="Entrance access" SizeInBit="32" */
	    DatapointSubType_15_0,		/*!< Id="DPST-15-0" Number="0" Name="DPT_Access_Data" Text="entrance access" */

	    DatapointType_16,			/*!< Id="DPT-16" Number="16" Name="Character string" Text="Character string" SizeInBit="112" */
	    DatapointSubType_16_0,		/*!< Id="DPST-16-0" Number="0" Name="DPT_String_ASCII" Text="Character String (ASCII)" */
	    DatapointSubType_16_1,		/*!< Id="DPST-16-1" Number="1" Name="DPT_String_8859_1" Text="Character String (ISO 8859-1)" */

	    DatapointType_17,			/*!< Id="DPT-17" Number="17" Name="Scene Number" Text="Scene Number" SizeInBit="8" */
	    DatapointSubType_17_1,		/*!< Id="DPST-17-1" Number="1" Name="DPT_SceneNumber" Text="scene number" */

	    DatapointType_18,			/*!< Id="DPT-18" Number="18" Name="Scene Control" Text="Scene Control" SizeInBit="8" */
	    DatapointSubType_18_1,		/*!< Id="DPST-18-1" Number="1" Name="DPT_SceneControl" Text="scene control" */

	    DatapointType_19,			/*!< Id="DPT-19" Number="19" Name="Date Time" Text="Date Time" SizeInBit="64" */
	    DatapointSubType_19_1,		/*!< Id="DPST-19-1" Number="1" Name="DPT_DateTime" Text="date time" */

	    DatapointType_20,			/*!< Id="DPT-20" Number="20" Name="1 byte" Text="1 byte" SizeInBit="8" */
	    DatapointSubType_20_1,		/*!< Id="DPST-20-1" Number="1" Name="DPT_SCLOMode" Text="SCLO mode" */
	    DatapointSubType_20_2,		/*!< Id="DPST-20-2" Number="2" Name="DPT_BuildingMode" Text="building mode" */
	    DatapointSubType_20_3,		/*!< Id="DPST-20-3" Number="3" Name="DPT_OccMode" Text="occupied" */
	    DatapointSubType_20_4,		/*!< Id="DPST-20-4" Number="4" Name="DPT_Priority" Text="priority" */
	    DatapointSubType_20_7,		/*!< Id="DPST-20-7" Number="7" Name="DPT_AlarmClassType" Text="alarm class" */
	    DatapointSubType_20_11,		/*!< Id="DPST-20-11" Number="11" Name="DPT_ErrorClass_System" Text="system error class" */
	    DatapointSubType_20_12,		/*!< Id="DPST-20-12" Number="12" Name="DPT_ErrorClass_HVAC" Text="HVAC error class" */
	    DatapointSubType_20_102,	/*!< Id="DPST-20-102" Number="102" Name="DPT_HVACMode" Text="HVAC mode" */
	    DatapointSubType_20_103,	/*!< Id="DPST-20-103" Number="103" Name="DPT_DHWMode" Text="DHW mode" */
	    DatapointSubType_20_104,	/*!< Id="DPST-20-104" Number="104" Name="DPT_LoadPriority" Text="load priority" */
	    DatapointSubType_20_105,	/*!< Id="DPST-20-105" Number="105" Name="DPT_HVACContrMode" Text="HVAC control mode" */
	    DatapointSubType_20_106,	/*!< Id="DPST-20-106" Number="106" Name="DPT_HVACEmergMode" Text="HVAC emergency mode" */
	    DatapointSubType_20_107,	/*!< Id="DPST-20-107" Number="107" Name="DPT_ChangeoverMode" Text="changeover mode" */
	    DatapointSubType_20_108,	/*!< Id="DPST-20-108" Number="108" Name="DPT_ValveMode" Text="valve mode" */
	    DatapointSubType_20_109,	/*!< Id="DPST-20-109" Number="109" Name="DPT_DamperMode" Text="damper mode" */
	    DatapointSubType_20_110,	/*!< Id="DPST-20-110" Number="110" Name="DPT_HeaterMode" Text="heater mode" */
	    DatapointSubType_20_111,	/*!< Id="DPST-20-111" Number="111" Name="DPT_FanMode" Text="fan mode" */
	    DatapointSubType_20_112,	/*!< Id="DPST-20-112" Number="112" Name="DPT_MasterSlaveMode" Text="master/slave mode" */
	    DatapointSubType_20_113,	/*!< Id="DPST-20-113" Number="113" Name="DPT_StatusRoomSetp" Text="status room setpoint" */

	    DatapointType_217,			/*!< Id="DPT-217" Number="217" Name="Version" Text="DPT Version" SizeInBit="16" */
	    DatapointSubType_217_1,		/*!< Id="DPST-217-1" Number="1" Name="DPT_Version" Text="DPT version" */

	    DatapointType_219,			/*!< Id="DPT-219" Number="219" Name="Alarm Info" Text="Alarm Info" SizeInBit="48" */
	    DatapointSubType_219_1,		/*!< Id="DPST-219-1" Number="1" Name="DPT_AlarmInfo" Text="alarm info" */

	    DatapointType_222,			/*!< Id="DPT-222" Number="222" Name="3x 16-Float Value" Text="3x 2 byte float value" SizeInBit="48" */
	    DatapointSubType_222_100,	/*!< Id="DPST-222-100" Number="100" Name="DPT_TempRoomSetpSetF16[3]" Text="room temperature setpoint" */
	    DatapointSubType_222_101	/*!< Id="DPST-222-101" Number="101" Name="DPT_TempRoomSetpSetShiftF16[3]" Text="room temperature setpoint shift" */
	};

	static int getTypeFromId(const std::string& datapointId);
};

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_DEFINES_DATAPOINT_TYPES_H__
