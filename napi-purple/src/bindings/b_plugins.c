#include "b_plugins.h"


napi_value create_object_from_plugin(napi_env env, PurplePlugin *plugin){
    napi_value obj;
    napi_create_object(env, &obj);
    /* info->name */
    napi_value name;
    napi_create_string_utf8(env, plugin->info->name, NAPI_AUTO_LENGTH, &name);
    napi_set_named_property(env, obj, "name", name);

    return obj;
}

napi_value _purple_plugins_get_protocols(napi_env env, napi_callback_info info) {
    napi_value protocol_array;
    napi_create_array(env, &protocol_array);
    GList* plugins = purple_plugins_get_protocols();
    GList* l;
    uint32_t i = 0;
    for (l = plugins; l != NULL; l = l->next)
    {
        PurplePlugin *plugin = (PurplePlugin*)l->data;
        napi_value obj = create_object_from_plugin(env, plugin);
        napi_set_element(env, protocol_array, i, obj);
        i++;
    }
    return protocol_array;
}
