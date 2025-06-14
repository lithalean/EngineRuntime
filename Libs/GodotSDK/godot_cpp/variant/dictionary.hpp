/**************************************************************************/
/*  dictionary.hpp                                                        */
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

#ifndef GODOT_CPP_DICTIONARY_HPP
#define GODOT_CPP_DICTIONARY_HPP

#include <godot_cpp/core/defs.hpp>

#include <gdextension_interface.h>

namespace godot {

class Array;
class Variant;

class Dictionary {
	static constexpr size_t DICTIONARY_SIZE = 8;
	uint8_t opaque[DICTIONARY_SIZE] = {};

	friend class Variant;

	static struct _MethodBindings {
		GDExtensionTypeFromVariantConstructorFunc from_variant_constructor;
		GDExtensionPtrConstructor constructor_0;
		GDExtensionPtrConstructor constructor_1;
		GDExtensionPtrDestructor destructor;
		GDExtensionPtrBuiltInMethod method_size;
		GDExtensionPtrBuiltInMethod method_is_empty;
		GDExtensionPtrBuiltInMethod method_clear;
		GDExtensionPtrBuiltInMethod method_merge;
		GDExtensionPtrBuiltInMethod method_merged;
		GDExtensionPtrBuiltInMethod method_has;
		GDExtensionPtrBuiltInMethod method_has_all;
		GDExtensionPtrBuiltInMethod method_find_key;
		GDExtensionPtrBuiltInMethod method_erase;
		GDExtensionPtrBuiltInMethod method_hash;
		GDExtensionPtrBuiltInMethod method_keys;
		GDExtensionPtrBuiltInMethod method_values;
		GDExtensionPtrBuiltInMethod method_duplicate;
		GDExtensionPtrBuiltInMethod method_get;
		GDExtensionPtrBuiltInMethod method_get_or_add;
		GDExtensionPtrBuiltInMethod method_make_read_only;
		GDExtensionPtrBuiltInMethod method_is_read_only;
		GDExtensionPtrBuiltInMethod method_recursive_equal;
		GDExtensionPtrIndexedSetter indexed_setter;
		GDExtensionPtrIndexedGetter indexed_getter;
		GDExtensionPtrKeyedSetter keyed_setter;
		GDExtensionPtrKeyedGetter keyed_getter;
		GDExtensionPtrKeyedChecker keyed_checker;
		GDExtensionPtrOperatorEvaluator operator_equal_Variant;
		GDExtensionPtrOperatorEvaluator operator_not_equal_Variant;
		GDExtensionPtrOperatorEvaluator operator_not;
		GDExtensionPtrOperatorEvaluator operator_equal_Dictionary;
		GDExtensionPtrOperatorEvaluator operator_not_equal_Dictionary;
		GDExtensionPtrOperatorEvaluator operator_in_Dictionary;
		GDExtensionPtrOperatorEvaluator operator_in_Array;
	} _method_bindings;

	static void init_bindings();
	static void _init_bindings_constructors_destructor();

	Dictionary(const Variant *p_variant);

public:
	_FORCE_INLINE_ GDExtensionTypePtr _native_ptr() const { return const_cast<uint8_t (*)[DICTIONARY_SIZE]>(&opaque); }
	Dictionary();
	Dictionary(const Dictionary &p_from);
	Dictionary(Dictionary &&p_other);
	~Dictionary();
	int64_t size() const;
	bool is_empty() const;
	void clear();
	void merge(const Dictionary &p_dictionary, bool p_overwrite = false);
	Dictionary merged(const Dictionary &p_dictionary, bool p_overwrite = false) const;
	bool has(const Variant &p_key) const;
	bool has_all(const Array &p_keys) const;
	Variant find_key(const Variant &p_value) const;
	bool erase(const Variant &p_key);
	int64_t hash() const;
	Array keys() const;
	Array values() const;
	Dictionary duplicate(bool p_deep = false) const;
	Variant get(const Variant &p_key, const Variant &p_default) const;
	Variant get_or_add(const Variant &p_key, const Variant &p_default);
	void make_read_only();
	bool is_read_only() const;
	bool recursive_equal(const Dictionary &p_dictionary, int64_t p_recursion_count) const;
	bool operator==(const Variant &p_other) const;
	bool operator!=(const Variant &p_other) const;
	bool operatornot() const;
	bool operator==(const Dictionary &p_other) const;
	bool operator!=(const Dictionary &p_other) const;
	Dictionary &operator=(const Dictionary &p_other);
	Dictionary &operator=(Dictionary &&p_other);
	const Variant &operator[](const Variant &p_key) const;
	Variant &operator[](const Variant &p_key);
};

} // namespace godot
#endif // ! GODOT_CPP_DICTIONARY_HPP