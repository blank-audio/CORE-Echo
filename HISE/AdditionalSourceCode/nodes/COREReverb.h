#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace COREReverb_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(xfader_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader_c0 = parameter::from0To1<core::gain<NV>, 
                                      0, 
                                      xfader_c0Range>;

template <int NV> using xfader_c1_0 = xfader_c0<NV>;

DECLARE_PARAMETER_RANGE_SKEW(xfader_c1_1Range, 
                             -100., 
                             5., 
                             5.42227);

template <int NV>
using xfader_c1_1 = parameter::from0To1<core::gain<NV>, 
                                        0, 
                                        xfader_c1_1Range>;

template <int NV>
using xfader_c1 = parameter::chain<ranges::Identity, 
                                   xfader_c1_0<NV>, 
                                   xfader_c1_1<NV>>;

template <int NV>
using xfader_multimod = parameter::list<xfader_c0<NV>, xfader_c1<NV>>;

template <int NV>
using xfader_t = control::xfader<xfader_multimod<NV>, faders::linear>;

template <int NV>
using chain3_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;

template <int NV>
using multi_t = container::multi<parameter::empty, 
                                 wrap::fix<1, core::gain<NV>>, 
                                 wrap::fix<1, core::gain<NV>>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, routing::ms_encode>, 
                                  multi_t<NV>, 
                                  routing::ms_decode>;

template <int NV>
using soft_bypass2_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, fx::reverb>, 
                                         filters::svf_eq<NV>, 
                                         chain1_t<NV>, 
                                         core::gain<NV>>;

template <int NV>
using soft_bypass2_t = bypass::smoothed<20, soft_bypass2_t_<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, soft_bypass2_t<NV>>>;
template <int NV>
using stereo_cable = cable::block<NV, 2>;

using sb3_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, core::fix_delay>>;

using sb3_t = bypass::smoothed<20, sb3_t_>;
using switcher1_c0 = parameter::bypass<sb3_t>;

template <int NV>
using tempo_sync1_t = wrap::mod<parameter::plain<core::fix_delay, 0>, 
                                control::tempo_sync<NV>>;

template <int NV>
using sb4_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, tempo_sync1_t<NV>>, 
                                core::fix_delay>;

template <int NV>
using sb4_t = bypass::smoothed<20, sb4_t_<NV>>;
template <int NV>
using switcher1_c1 = parameter::bypass<sb4_t<NV>>;

template <int NV>
using switcher1_multimod = parameter::list<switcher1_c0, switcher1_c1<NV>>;

template <int NV>
using switcher1_t = control::xfader<switcher1_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container1_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb3_t>, 
                                         sb4_t<NV>>;

template <int NV>
using softbypass_switch4_t = container::chain<parameter::empty, 
                                              wrap::fix<2, routing::receive<NV, stereo_cable<NV>>>, 
                                              switcher1_t<NV>, 
                                              sb_container1_t<NV>, 
                                              routing::send<NV, stereo_cable<NV>>>;

template <int NV> using multi1_t = multi_t<NV>;

template <int NV>
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<2, routing::ms_encode>, 
                                  multi1_t<NV>, 
                                  routing::ms_decode>;

template <int NV>
using soft_bypass_t_ = container::chain<parameter::empty, 
                                        wrap::fix<2, fx::reverb>, 
                                        filters::svf_eq<NV>, 
                                        chain4_t<NV>, 
                                        core::gain<NV>>;

template <int NV>
using soft_bypass_t = bypass::smoothed<20, soft_bypass_t_<NV>>;

template <int NV>
using soft_bypass3_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, softbypass_switch4_t<NV>>, 
                                         soft_bypass_t<NV>>;

template <int NV>
using soft_bypass3_t = bypass::smoothed<20, soft_bypass3_t_<NV>>;

template <int NV>
using chain2_t = container::chain<parameter::empty, 
                                  wrap::fix<2, soft_bypass3_t<NV>>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain3_t<NV>>, 
                                 chain_t<NV>, 
                                 chain2_t<NV>>;

template <int NV>
using soft_bypass1_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, xfader_t<NV>>, 
                                         split_t<NV>>;

template <int NV>
using soft_bypass1_t = bypass::smoothed<20, soft_bypass1_t_<NV>>;

namespace COREReverb_t_parameters
{
// Parameter list for COREReverb_impl::COREReverb_t ------------------------------------------------

using Size = parameter::chain<ranges::Identity, 
                              parameter::plain<fx::reverb, 2>, 
                              parameter::plain<fx::reverb, 2>>;

DECLARE_PARAMETER_RANGE_SKEW(Tone_0Range, 
                             200., 
                             20000., 
                             0.988473);

template <int NV>
using Tone_0 = parameter::from0To1<filters::svf_eq<NV>, 
                                   0, 
                                   Tone_0Range>;

DECLARE_PARAMETER_RANGE_SKEW(Tone_1Range, 
                             20., 
                             20000., 
                             0.988473);

template <int NV>
using Tone_1 = parameter::from0To1<filters::svf_eq<NV>, 
                                   0, 
                                   Tone_1Range>;

template <int NV>
using Tone = parameter::chain<ranges::Identity, 
                              Tone_0<NV>, 
                              Tone_1<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(Width_0Range, 
                             -100., 
                             10., 
                             5.42227);

template <int NV>
using Width_0 = parameter::from0To1<core::gain<NV>, 
                                    0, 
                                    Width_0Range>;

template <int NV>
using Width_1 = parameter::from0To1<core::gain<NV>, 
                                    0, 
                                    COREReverb_impl::xfader_c0Range>;

template <int NV>
using Width = parameter::chain<ranges::Identity, 
                               Width_0<NV>, 
                               Width_1<NV>>;

DECLARE_PARAMETER_RANGE_INV(Mix_InputRange, 
                            0., 
                            1.);
template <int NV>
using Mix_0 = parameter::bypass<COREReverb_impl::soft_bypass1_t<NV>>;

template <int NV>
using Mix = parameter::chain<Mix_InputRange, 
                             Mix_0<NV>, 
                             Mix_0<NV>>;

using Damp = parameter::chain<ranges::Identity, 
                              parameter::plain<fx::reverb, 0>, 
                              parameter::plain<fx::reverb, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(DelayTimeRange, 
                             0., 
                             1000., 
                             0.30103);

using DelayTime = parameter::from0To1<core::fix_delay, 
                                      0, 
                                      DelayTimeRange>;

DECLARE_PARAMETER_RANGE_STEP(TempoSync_0Range, 
                             0., 
                             1., 
                             1.);

template <int NV>
using TempoSync_0 = parameter::from0To1<COREReverb_impl::tempo_sync1_t<NV>, 
                                        2, 
                                        TempoSync_0Range>;

template <int NV>
using TempoSync = parameter::chain<ranges::Identity, 
                                   TempoSync_0<NV>, 
                                   parameter::plain<COREReverb_impl::switcher1_t<NV>, 0>>;

template <int NV>
using REVERBSWITCH_0 = parameter::bypass<COREReverb_impl::soft_bypass2_t<NV>>;

template <int NV>
using REVERBSWITCH_1 = parameter::bypass<COREReverb_impl::soft_bypass_t<NV>>;

template <int NV>
using REVERBSWITCH = parameter::chain<ranges::Identity, 
                                      REVERBSWITCH_0<NV>, 
                                      REVERBSWITCH_1<NV>>;

template <int NV>
using DELAYSWITCH = parameter::bypass<COREReverb_impl::soft_bypass3_t<NV>>;

DECLARE_PARAMETER_RANGE(Tempo_InputRange, 
                        1., 
                        18.);
DECLARE_PARAMETER_RANGE_STEP(Tempo_0Range, 
                             0., 
                             18., 
                             1.);

template <int NV>
using Tempo_0 = parameter::from0To1<COREReverb_impl::tempo_sync1_t<NV>, 
                                    0, 
                                    Tempo_0Range>;

template <int NV>
using Tempo = parameter::chain<Tempo_InputRange, Tempo_0<NV>>;

template <int NV>
using Feedback = parameter::plain<routing::receive<NV, stereo_cable<NV>>, 
                                  0>;
template <int NV>
using EffectMix = parameter::plain<COREReverb_impl::xfader_t<NV>, 
                                   0>;
template <int NV>
using COREReverb_t_plist = parameter::list<Size, 
                                           Tone<NV>, 
                                           Width<NV>, 
                                           Mix<NV>, 
                                           Damp, 
                                           DelayTime, 
                                           Feedback<NV>, 
                                           EffectMix<NV>, 
                                           TempoSync<NV>, 
                                           REVERBSWITCH<NV>, 
                                           DELAYSWITCH<NV>, 
                                           Tempo<NV>>;
}

template <int NV>
using COREReverb_t_ = container::chain<COREReverb_t_parameters::COREReverb_t_plist<NV>, 
                                       wrap::fix<2, soft_bypass1_t<NV>>, 
                                       core::gain<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public COREReverb_impl::COREReverb_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(COREReverb);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(210)
		{
			0x005C, 0x0000, 0x0000, 0x6953, 0x657A, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F00, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0001, 0x0000, 0x6F54, 0x656E, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F00, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0002, 0x0000, 0x6957, 0x7464, 0x0068, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x0000, 0x003F, 0x8000, 0x003F, 0x0000, 
            0x5C00, 0x0300, 0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x005C, 0x0004, 0x0000, 0x6144, 0x706D, 0x0000, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x1EB8, 0x3F05, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x035C, 0x0005, 0x0000, 0x6544, 0x616C, 0x5479, 0x6D69, 0x0065, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x9A3F, 0x1999, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5C00, 0x0600, 0x0000, 0x4600, 0x6565, 0x6264, 
            0x6361, 0x006B, 0x0000, 0x0000, 0x0000, 0x8000, 0x5C3F, 0x028F, 
            0x003F, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0700, 0x0000, 0x4500, 
            0x6666, 0x6365, 0x4D74, 0x7869, 0x0000, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x3D71, 0x3F0A, 0x0000, 0x3F80, 0x0000, 0x0000, 0x005C, 
            0x0008, 0x0000, 0x6554, 0x706D, 0x536F, 0x6E79, 0x0063, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5C00, 0x0900, 0x0000, 0x5200, 0x5645, 0x5245, 0x5342, 
            0x4957, 0x4354, 0x0048, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x5C00, 0x0A00, 0x0000, 
            0x4400, 0x4C45, 0x5941, 0x5753, 0x5449, 0x4843, 0x0000, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x005C, 0x000B, 0x0000, 0x6554, 0x706D, 0x006F, 0x0000, 
            0x8000, 0x003F, 0x9000, 0x0041, 0x4000, 0x0040, 0x8000, 0x003F, 
            0x0000, 0x0000
		};
		SNEX_METADATA_ENCODED_MOD_INFO(2)
		{
			0x3D3B, 0x003E
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& soft_bypass1 = this->getT(0);                                               // COREReverb_impl::soft_bypass1_t<NV>
		auto& xfader = this->getT(0).getT(0);                                             // COREReverb_impl::xfader_t<NV>
		auto& split = this->getT(0).getT(1);                                              // COREReverb_impl::split_t<NV>
		auto& chain3 = this->getT(0).getT(1).getT(0);                                     // COREReverb_impl::chain3_t<NV>
		auto& gain6 = this->getT(0).getT(1).getT(0).getT(0);                              // core::gain<NV>
		auto& chain = this->getT(0).getT(1).getT(1);                                      // COREReverb_impl::chain_t<NV>
		auto& soft_bypass2 = this->getT(0).getT(1).getT(1).getT(0);                       // COREReverb_impl::soft_bypass2_t<NV>
		auto& reverb1 = this->getT(0).getT(1).getT(1).getT(0).getT(0);                    // fx::reverb
		auto& svf_eq = this->getT(0).getT(1).getT(1).getT(0).getT(1);                     // filters::svf_eq<NV>
		auto& chain1 = this->getT(0).getT(1).getT(1).getT(0).getT(2);                     // COREReverb_impl::chain1_t<NV>
		auto& ms_encode = this->getT(0).getT(1).getT(1).getT(0).getT(2).getT(0);          // routing::ms_encode
		auto& multi = this->getT(0).getT(1).getT(1).getT(0).getT(2).getT(1);              // COREReverb_impl::multi_t<NV>
		auto& gain = this->getT(0).getT(1).getT(1).getT(0).getT(2).getT(1).getT(0);       // core::gain<NV>
		auto& gain1 = this->getT(0).getT(1).getT(1).getT(0).getT(2).getT(1).getT(1);      // core::gain<NV>
		auto& ms_decode = this->getT(0).getT(1).getT(1).getT(0).getT(2).getT(2);          // routing::ms_decode
		auto& gain5 = this->getT(0).getT(1).getT(1).getT(0).getT(3);                      // core::gain<NV>
		auto& chain2 = this->getT(0).getT(1).getT(2);                                     // COREReverb_impl::chain2_t<NV>
		auto& soft_bypass3 = this->getT(0).getT(1).getT(2).getT(0);                       // COREReverb_impl::soft_bypass3_t<NV>
		auto& softbypass_switch4 = this->getT(0).getT(1).getT(2).getT(0).getT(0);         // COREReverb_impl::softbypass_switch4_t<NV>
		auto& receive1 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(0);           // routing::receive<NV, stereo_cable<NV>>
		auto& switcher1 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(1);          // COREReverb_impl::switcher1_t<NV>
		auto& sb_container1 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(2);      // COREReverb_impl::sb_container1_t<NV>
		auto& sb3 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(2).getT(0);        // COREReverb_impl::sb3_t
		auto& fix_delay1 = this->getT(0).getT(1).getT(2).getT(0).                         // core::fix_delay
                           getT(0).getT(2).getT(0).getT(0);
		auto& sb4 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(2).getT(1);        // COREReverb_impl::sb4_t<NV>
		auto& tempo_sync1 = this->getT(0).getT(1).getT(2).getT(0).                        // COREReverb_impl::tempo_sync1_t<NV>
                            getT(0).getT(2).getT(1).getT(0);
		auto& fix_delay3 = this->getT(0).getT(1).getT(2).getT(0).                         // core::fix_delay
                           getT(0).getT(2).getT(1).getT(1);
		auto& send1 = this->getT(0).getT(1).getT(2).getT(0).getT(0).getT(3);              // routing::send<NV, stereo_cable<NV>>
		auto& soft_bypass = this->getT(0).getT(1).getT(2).getT(0).getT(1);                // COREReverb_impl::soft_bypass_t<NV>
		auto& reverb = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(0);             // fx::reverb
		auto& svf_eq1 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(1);            // filters::svf_eq<NV>
		auto& chain4 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(2);             // COREReverb_impl::chain4_t<NV>
		auto& ms_encode1 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(2).getT(0); // routing::ms_encode
		auto& multi1 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(2).getT(1);     // COREReverb_impl::multi1_t<NV>
		auto& gain4 = this->getT(0).getT(1).getT(2).getT(0).                              // core::gain<NV>
                      getT(1).getT(2).getT(1).getT(0);
		auto& gain7 = this->getT(0).getT(1).getT(2).getT(0).                              // core::gain<NV>
                      getT(1).getT(2).getT(1).getT(1);
		auto& ms_decode1 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(2).getT(2); // routing::ms_decode
		auto& gain2 = this->getT(0).getT(1).getT(2).getT(0).getT(1).getT(3);              // core::gain<NV>
		auto& gain10 = this->getT(1);                                                     // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& Size_p = this->getParameterT(0);
		Size_p.connectT(0, reverb1); // Size -> reverb1::Size
		Size_p.connectT(1, reverb);  // Size -> reverb::Size
		
		auto& Tone_p = this->getParameterT(1);
		Tone_p.connectT(0, svf_eq);  // Tone -> svf_eq::Frequency
		Tone_p.connectT(1, svf_eq1); // Tone -> svf_eq1::Frequency
		
		auto& Width_p = this->getParameterT(2);
		Width_p.connectT(0, gain1); // Width -> gain1::Gain
		Width_p.connectT(1, gain7); // Width -> gain7::Gain
		
		auto& Mix_p = this->getParameterT(3);
		Mix_p.connectT(0, soft_bypass1); // Mix -> soft_bypass1::Bypassed
		Mix_p.connectT(1, soft_bypass1); // Mix -> soft_bypass1::Bypassed
		
		auto& Damp_p = this->getParameterT(4);
		Damp_p.connectT(0, reverb1); // Damp -> reverb1::Damping
		Damp_p.connectT(1, reverb);  // Damp -> reverb::Damping
		
		this->getParameterT(5).connectT(0, fix_delay1); // DelayTime -> fix_delay1::DelayTime
		
		this->getParameterT(6).connectT(0, receive1); // Feedback -> receive1::Feedback
		
		this->getParameterT(7).connectT(0, xfader); // EffectMix -> xfader::Value
		
		auto& TempoSync_p = this->getParameterT(8);
		TempoSync_p.connectT(0, tempo_sync1); // TempoSync -> tempo_sync1::Enabled
		TempoSync_p.connectT(1, switcher1);   // TempoSync -> switcher1::Value
		
		auto& REVERBSWITCH_p = this->getParameterT(9);
		REVERBSWITCH_p.connectT(0, soft_bypass2); // REVERBSWITCH -> soft_bypass2::Bypassed
		REVERBSWITCH_p.connectT(1, soft_bypass);  // REVERBSWITCH -> soft_bypass::Bypassed
		
		this->getParameterT(10).connectT(0, soft_bypass3); // DELAYSWITCH -> soft_bypass3::Bypassed
		
		this->getParameterT(11).connectT(0, tempo_sync1); // Tempo -> tempo_sync1::Tempo
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain6);       // xfader -> gain6::Gain
		xfader_p.getParameterT(1).connectT(0, gain2);       // xfader -> gain2::Gain
		xfader_p.getParameterT(1).connectT(1, gain5);       // xfader -> gain5::Gain
		tempo_sync1.getParameter().connectT(0, fix_delay3); // tempo_sync1 -> fix_delay3::DelayTime
		auto& switcher1_p = switcher1.getWrappedObject().getParameter();
		switcher1_p.getParameterT(0).connectT(0, sb3); // switcher1 -> sb3::Bypassed
		switcher1_p.getParameterT(1).connectT(0, sb4); // switcher1 -> sb4::Bypassed
		
		// Send Connections ------------------------------------------------------------------------
		
		send1.connect(receive1);
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                            // gain6::Gain is automated
		gain6.setParameterT(1, 20.); // core::gain::Smoothing
		gain6.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // reverb1::Damping is automated
		reverb1.setParameterT(1, 0.5); // fx::reverb::Width
		;                              // reverb1::Size is automated
		
		;                                    // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 1.);         // filters::svf_eq::Q
		svf_eq.setParameterT(2, 0.);         // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.00482097); // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 0.);         // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);         // filters::svf_eq::Enabled
		
		gain.setParameterT(0, 0.);  // core::gain::Gain
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain5::Gain is automated
		gain5.setParameterT(1, 20.); // core::gain::Smoothing
		gain5.setParameterT(2, 0.);  // core::gain::ResetValue
		
		softbypass_switch4.setParameterT(0, 0.); // container::chain::Switch
		
		; // receive1::Feedback is automated
		
		; // switcher1::Value is automated
		
		;                                  // fix_delay1::DelayTime is automated
		fix_delay1.setParameterT(1, 512.); // core::fix_delay::FadeTime
		
		;                                 // tempo_sync1::Tempo is automated
		tempo_sync1.setParameterT(1, 0.); // control::tempo_sync::Multiplier
		;                                 // tempo_sync1::Enabled is automated
		tempo_sync1.setParameterT(3, 0.); // control::tempo_sync::UnsyncedTime
		
		;                                  // fix_delay3::DelayTime is automated
		fix_delay3.setParameterT(1, 512.); // core::fix_delay::FadeTime
		
		;                             // reverb::Damping is automated
		reverb.setParameterT(1, 0.5); // fx::reverb::Width
		;                             // reverb::Size is automated
		
		;                               // svf_eq1::Frequency is automated
		svf_eq1.setParameterT(1, 1.);   // filters::svf_eq::Q
		svf_eq1.setParameterT(2, 0.);   // filters::svf_eq::Gain
		svf_eq1.setParameterT(3, 0.01); // filters::svf_eq::Smoothing
		svf_eq1.setParameterT(4, 0.);   // filters::svf_eq::Mode
		svf_eq1.setParameterT(5, 1.);   // filters::svf_eq::Enabled
		
		gain4.setParameterT(0, 0.);  // core::gain::Gain
		gain4.setParameterT(1, 20.); // core::gain::Smoothing
		gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain7::Gain is automated
		gain7.setParameterT(1, 20.); // core::gain::Smoothing
		gain7.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // gain2::Gain is automated
		gain2.setParameterT(1, 305.5); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);    // core::gain::ResetValue
		
		gain10.setParameterT(0, 2.5); // core::gain::Gain
		gain10.setParameterT(1, 20.); // core::gain::Smoothing
		gain10.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.5);
		this->setParameterT(1, 0.5);
		this->setParameterT(2, 0.5);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 0.52);
		this->setParameterT(5, 0.6);
		this->setParameterT(6, 0.51);
		this->setParameterT(7, 0.54);
		this->setParameterT(8, 1.);
		this->setParameterT(9, 1.);
		this->setParameterT(10, 1.);
		this->setParameterT(11, 3.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using COREReverb = wrap::node<COREReverb_impl::instance<NV>>;
}


