#include "gdop_user_array.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOPUserArray::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_users"), &GDOPUserArray::get_users);
    ClassDB::bind_method(D_METHOD("set_users", "users_array"), &GDOPUserArray::set_users);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "users"), "set_users", "get_users");

    ClassDB::bind_method(D_METHOD("get_has_next_page"), &GDOPUserArray::get_has_next_page);

	ClassDB::bind_method(D_METHOD("add_users", "users_array"), &GDOPUserArray::add_users);
}

GDOPUserArray::GDOPUserArray() {}
GDOPUserArray::GDOPUserArray(ovrUserArrayHandle p_array_handle) {
	array_handle = p_array_handle;
}
GDOPUserArray::~GDOPUserArray() {}

bool GDOPUserArray::get_has_next_page() const {
    return has_next_page;
}

Array GDOPUserArray::get_users() const {
    return users;
}

void GDOPUserArray::set_users(const Array p_users_array) {
    users = p_users_array;
}

void GDOPUserArray::add_users(Array p_users_array) {
    users.append_array(p_users_array);
}