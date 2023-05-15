#ifndef GDOCULUSPLATFORM_H
#define GDOCULUSPLATFORM_H

#include <include/OVR_Platform.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "gop_promise.h"

namespace godot {

class GDOculusPlatform : public Object {
	GDCLASS(GDOculusPlatform, Object)

protected:
	static GDOculusPlatform *singleton;
	static void _bind_methods();

private:
	Vector<Ref<GDOculusPlatformPromise>> _promises;
	Vector<Ref<GDOculusPlatformPromise>> _promises_to_reject;

	bool _get_promise(uint64_t p_promise_id, Ref<GDOculusPlatformPromise> &p_promise);
	uint64_t _get_reject_promise_id();
	void _reject_promises();

	uint64_t _last_promise_rejected_id = 0;

#ifdef __ANDROID__
	bool _get_env(JNIEnv **p_env);

	void _handle_default_process_error(ovrMessageHandle p_message, ovrRequest p_msg_id, Ref<GDOculusPlatformPromise> &p_promise);

	void _process_initialize_android_async(ovrMessageHandle p_message);

	// USER
	void _process_get_is_viewer_entitled(ovrMessageHandle p_message);
	void _process_get_logged_in_user(ovrMessageHandle p_message);
	void _process_get_user_proof(ovrMessageHandle p_message);
	void _process_get_user_access_token(ovrMessageHandle p_message);
	void _process_get_blocked_users(ovrMessageHandle p_message);
	void _process_get_logged_in_user_friends(ovrMessageHandle p_message);
	void _process_get_org_scoped_id(ovrMessageHandle p_message);
	void _process_get_sdk_accounts(ovrMessageHandle p_message);
	void _process_launch_block_flow(ovrMessageHandle p_message);
	void _process_launch_unblock_flow(ovrMessageHandle p_message);
	void _process_launch_friend_request_flow(ovrMessageHandle p_message);

	// USER HELPERS
	Dictionary _get_user_information(ovrUserHandle p_user_handle);

	void _handle_unhandled_message(ovrMessageHandle p_message);

#endif

public:
	static GDOculusPlatform *get_singleton();
	GDOculusPlatform();
	~GDOculusPlatform();

	bool initialize_android(String p_app_id);
	Ref<GDOculusPlatformPromise> initialize_android_async(String p_app_id);

	// USER
	Ref<GDOculusPlatformPromise> get_is_viewer_entitled();
	Ref<GDOculusPlatformPromise> get_user(String p_user_id);
	Ref<GDOculusPlatformPromise> get_logged_in_user();
	Ref<GDOculusPlatformPromise> get_user_proof();
	Ref<GDOculusPlatformPromise> get_user_access_token();
	Ref<GDOculusPlatformPromise> get_blocked_users();
	Ref<GDOculusPlatformPromise> get_logged_in_user_friends();
	Ref<GDOculusPlatformPromise> get_org_scoped_id(String p_user_id);
	Ref<GDOculusPlatformPromise> get_sdk_accounts();
	Ref<GDOculusPlatformPromise> launch_block_flow(String p_user_id);
	Ref<GDOculusPlatformPromise> launch_unblock_flow(String p_user_id);
	Ref<GDOculusPlatformPromise> launch_friend_request_flow(String p_user_id);

	void pump_messages();
};

} // namespace godot

#endif // GDOCULUSPLATFORM_H
