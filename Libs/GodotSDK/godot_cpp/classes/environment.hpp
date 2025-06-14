/**************************************************************************/
/*  environment.hpp                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

// THIS FILE IS GENERATED. EDITS WILL BE LOST.

#ifndef GODOT_CPP_ENVIRONMENT_HPP
#define GODOT_CPP_ENVIRONMENT_HPP

#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <godot_cpp/core/class_db.hpp>

#include <type_traits>

namespace godot {

class Sky;
class Texture;

class Environment : public Resource {
	GDEXTENSION_CLASS(Environment, Resource)

public:

	enum BGMode {
		BG_CLEAR_COLOR = 0,
		BG_COLOR = 1,
		BG_SKY = 2,
		BG_CANVAS = 3,
		BG_KEEP = 4,
		BG_CAMERA_FEED = 5,
		BG_MAX = 6,
	};

	enum AmbientSource {
		AMBIENT_SOURCE_BG = 0,
		AMBIENT_SOURCE_DISABLED = 1,
		AMBIENT_SOURCE_COLOR = 2,
		AMBIENT_SOURCE_SKY = 3,
	};

	enum ReflectionSource {
		REFLECTION_SOURCE_BG = 0,
		REFLECTION_SOURCE_DISABLED = 1,
		REFLECTION_SOURCE_SKY = 2,
	};

	enum ToneMapper {
		TONE_MAPPER_LINEAR = 0,
		TONE_MAPPER_REINHARDT = 1,
		TONE_MAPPER_FILMIC = 2,
		TONE_MAPPER_ACES = 3,
	};

	enum GlowBlendMode {
		GLOW_BLEND_MODE_ADDITIVE = 0,
		GLOW_BLEND_MODE_SCREEN = 1,
		GLOW_BLEND_MODE_SOFTLIGHT = 2,
		GLOW_BLEND_MODE_REPLACE = 3,
		GLOW_BLEND_MODE_MIX = 4,
	};

	enum FogMode {
		FOG_MODE_EXPONENTIAL = 0,
		FOG_MODE_DEPTH = 1,
	};

	enum SDFGIYScale {
		SDFGI_Y_SCALE_50_PERCENT = 0,
		SDFGI_Y_SCALE_75_PERCENT = 1,
		SDFGI_Y_SCALE_100_PERCENT = 2,
	};

	void set_background(Environment::BGMode p_mode);
	Environment::BGMode get_background() const;
	void set_sky(const Ref<Sky> &p_sky);
	Ref<Sky> get_sky() const;
	void set_sky_custom_fov(double p_scale);
	double get_sky_custom_fov() const;
	void set_sky_rotation(const Vector3 &p_euler_radians);
	Vector3 get_sky_rotation() const;
	void set_bg_color(const Color &p_color);
	Color get_bg_color() const;
	void set_bg_energy_multiplier(double p_energy);
	double get_bg_energy_multiplier() const;
	void set_bg_intensity(double p_energy);
	double get_bg_intensity() const;
	void set_canvas_max_layer(int32_t p_layer);
	int32_t get_canvas_max_layer() const;
	void set_camera_feed_id(int32_t p_id);
	int32_t get_camera_feed_id() const;
	void set_ambient_light_color(const Color &p_color);
	Color get_ambient_light_color() const;
	void set_ambient_source(Environment::AmbientSource p_source);
	Environment::AmbientSource get_ambient_source() const;
	void set_ambient_light_energy(double p_energy);
	double get_ambient_light_energy() const;
	void set_ambient_light_sky_contribution(double p_ratio);
	double get_ambient_light_sky_contribution() const;
	void set_reflection_source(Environment::ReflectionSource p_source);
	Environment::ReflectionSource get_reflection_source() const;
	void set_tonemapper(Environment::ToneMapper p_mode);
	Environment::ToneMapper get_tonemapper() const;
	void set_tonemap_exposure(double p_exposure);
	double get_tonemap_exposure() const;
	void set_tonemap_white(double p_white);
	double get_tonemap_white() const;
	void set_ssr_enabled(bool p_enabled);
	bool is_ssr_enabled() const;
	void set_ssr_max_steps(int32_t p_max_steps);
	int32_t get_ssr_max_steps() const;
	void set_ssr_fade_in(double p_fade_in);
	double get_ssr_fade_in() const;
	void set_ssr_fade_out(double p_fade_out);
	double get_ssr_fade_out() const;
	void set_ssr_depth_tolerance(double p_depth_tolerance);
	double get_ssr_depth_tolerance() const;
	void set_ssao_enabled(bool p_enabled);
	bool is_ssao_enabled() const;
	void set_ssao_radius(double p_radius);
	double get_ssao_radius() const;
	void set_ssao_intensity(double p_intensity);
	double get_ssao_intensity() const;
	void set_ssao_power(double p_power);
	double get_ssao_power() const;
	void set_ssao_detail(double p_detail);
	double get_ssao_detail() const;
	void set_ssao_horizon(double p_horizon);
	double get_ssao_horizon() const;
	void set_ssao_sharpness(double p_sharpness);
	double get_ssao_sharpness() const;
	void set_ssao_direct_light_affect(double p_amount);
	double get_ssao_direct_light_affect() const;
	void set_ssao_ao_channel_affect(double p_amount);
	double get_ssao_ao_channel_affect() const;
	void set_ssil_enabled(bool p_enabled);
	bool is_ssil_enabled() const;
	void set_ssil_radius(double p_radius);
	double get_ssil_radius() const;
	void set_ssil_intensity(double p_intensity);
	double get_ssil_intensity() const;
	void set_ssil_sharpness(double p_sharpness);
	double get_ssil_sharpness() const;
	void set_ssil_normal_rejection(double p_normal_rejection);
	double get_ssil_normal_rejection() const;
	void set_sdfgi_enabled(bool p_enabled);
	bool is_sdfgi_enabled() const;
	void set_sdfgi_cascades(int32_t p_amount);
	int32_t get_sdfgi_cascades() const;
	void set_sdfgi_min_cell_size(double p_size);
	double get_sdfgi_min_cell_size() const;
	void set_sdfgi_max_distance(double p_distance);
	double get_sdfgi_max_distance() const;
	void set_sdfgi_cascade0_distance(double p_distance);
	double get_sdfgi_cascade0_distance() const;
	void set_sdfgi_y_scale(Environment::SDFGIYScale p_scale);
	Environment::SDFGIYScale get_sdfgi_y_scale() const;
	void set_sdfgi_use_occlusion(bool p_enable);
	bool is_sdfgi_using_occlusion() const;
	void set_sdfgi_bounce_feedback(double p_amount);
	double get_sdfgi_bounce_feedback() const;
	void set_sdfgi_read_sky_light(bool p_enable);
	bool is_sdfgi_reading_sky_light() const;
	void set_sdfgi_energy(double p_amount);
	double get_sdfgi_energy() const;
	void set_sdfgi_normal_bias(double p_bias);
	double get_sdfgi_normal_bias() const;
	void set_sdfgi_probe_bias(double p_bias);
	double get_sdfgi_probe_bias() const;
	void set_glow_enabled(bool p_enabled);
	bool is_glow_enabled() const;
	void set_glow_level(int32_t p_idx, double p_intensity);
	double get_glow_level(int32_t p_idx) const;
	void set_glow_normalized(bool p_normalize);
	bool is_glow_normalized() const;
	void set_glow_intensity(double p_intensity);
	double get_glow_intensity() const;
	void set_glow_strength(double p_strength);
	double get_glow_strength() const;
	void set_glow_mix(double p_mix);
	double get_glow_mix() const;
	void set_glow_bloom(double p_amount);
	double get_glow_bloom() const;
	void set_glow_blend_mode(Environment::GlowBlendMode p_mode);
	Environment::GlowBlendMode get_glow_blend_mode() const;
	void set_glow_hdr_bleed_threshold(double p_threshold);
	double get_glow_hdr_bleed_threshold() const;
	void set_glow_hdr_bleed_scale(double p_scale);
	double get_glow_hdr_bleed_scale() const;
	void set_glow_hdr_luminance_cap(double p_amount);
	double get_glow_hdr_luminance_cap() const;
	void set_glow_map_strength(double p_strength);
	double get_glow_map_strength() const;
	void set_glow_map(const Ref<Texture> &p_mode);
	Ref<Texture> get_glow_map() const;
	void set_fog_enabled(bool p_enabled);
	bool is_fog_enabled() const;
	void set_fog_mode(Environment::FogMode p_mode);
	Environment::FogMode get_fog_mode() const;
	void set_fog_light_color(const Color &p_light_color);
	Color get_fog_light_color() const;
	void set_fog_light_energy(double p_light_energy);
	double get_fog_light_energy() const;
	void set_fog_sun_scatter(double p_sun_scatter);
	double get_fog_sun_scatter() const;
	void set_fog_density(double p_density);
	double get_fog_density() const;
	void set_fog_height(double p_height);
	double get_fog_height() const;
	void set_fog_height_density(double p_height_density);
	double get_fog_height_density() const;
	void set_fog_aerial_perspective(double p_aerial_perspective);
	double get_fog_aerial_perspective() const;
	void set_fog_sky_affect(double p_sky_affect);
	double get_fog_sky_affect() const;
	void set_fog_depth_curve(double p_curve);
	double get_fog_depth_curve() const;
	void set_fog_depth_begin(double p_begin);
	double get_fog_depth_begin() const;
	void set_fog_depth_end(double p_end);
	double get_fog_depth_end() const;
	void set_volumetric_fog_enabled(bool p_enabled);
	bool is_volumetric_fog_enabled() const;
	void set_volumetric_fog_emission(const Color &p_color);
	Color get_volumetric_fog_emission() const;
	void set_volumetric_fog_albedo(const Color &p_color);
	Color get_volumetric_fog_albedo() const;
	void set_volumetric_fog_density(double p_density);
	double get_volumetric_fog_density() const;
	void set_volumetric_fog_emission_energy(double p_begin);
	double get_volumetric_fog_emission_energy() const;
	void set_volumetric_fog_anisotropy(double p_anisotropy);
	double get_volumetric_fog_anisotropy() const;
	void set_volumetric_fog_length(double p_length);
	double get_volumetric_fog_length() const;
	void set_volumetric_fog_detail_spread(double p_detail_spread);
	double get_volumetric_fog_detail_spread() const;
	void set_volumetric_fog_gi_inject(double p_gi_inject);
	double get_volumetric_fog_gi_inject() const;
	void set_volumetric_fog_ambient_inject(double p_enabled);
	double get_volumetric_fog_ambient_inject() const;
	void set_volumetric_fog_sky_affect(double p_sky_affect);
	double get_volumetric_fog_sky_affect() const;
	void set_volumetric_fog_temporal_reprojection_enabled(bool p_enabled);
	bool is_volumetric_fog_temporal_reprojection_enabled() const;
	void set_volumetric_fog_temporal_reprojection_amount(double p_temporal_reprojection_amount);
	double get_volumetric_fog_temporal_reprojection_amount() const;
	void set_adjustment_enabled(bool p_enabled);
	bool is_adjustment_enabled() const;
	void set_adjustment_brightness(double p_brightness);
	double get_adjustment_brightness() const;
	void set_adjustment_contrast(double p_contrast);
	double get_adjustment_contrast() const;
	void set_adjustment_saturation(double p_saturation);
	double get_adjustment_saturation() const;
	void set_adjustment_color_correction(const Ref<Texture> &p_color_correction);
	Ref<Texture> get_adjustment_color_correction() const;
protected:
	template <typename T, typename B>
	static void register_virtuals() {
		Resource::register_virtuals<T, B>();
	}

public:

};

} // namespace godot

VARIANT_ENUM_CAST(Environment::BGMode);
VARIANT_ENUM_CAST(Environment::AmbientSource);
VARIANT_ENUM_CAST(Environment::ReflectionSource);
VARIANT_ENUM_CAST(Environment::ToneMapper);
VARIANT_ENUM_CAST(Environment::GlowBlendMode);
VARIANT_ENUM_CAST(Environment::FogMode);
VARIANT_ENUM_CAST(Environment::SDFGIYScale);

#endif // ! GODOT_CPP_ENVIRONMENT_HPP