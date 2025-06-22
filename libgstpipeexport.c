#include <stdio.h>
#include <stdlib.h>

#include "ezinject_module.h"

#include <gst/gst.h>
#include <gst/gstdebugutils.h>

#ifndef LOG_RESERVED_HANDLE
  #define LOG_RESERVED_HANDLE stdout
#endif

#ifndef __LOG_DECLARE_VERBOSITY
#define __LOG_DECLARE_VERBOSITY(verb) \
  enum verbosity_level verbosity = verb
#endif

#ifndef LOG_SETUP
#define LOG_SETUP(verb) \
  FILE *LOG_RESERVED_HANDLE; \
  __LOG_DECLARE_VERBOSITY(verb)
#endif

LOG_SETUP(V_DBG);

static const char *log_path = "/tmp/gstpipeexport.log";
static const char *dot_path = "/tmp/pipeline_dump.dot";


typedef GstStateChangeReturn (*gst_element_set_state_t)(GstElement *element, GstState state);
static gst_element_set_state_t orig_gst_element_set_state = NULL;

static GstElement *saved_pipeline = NULL;
static bool pipeline_dumped = false;


GstStateChangeReturn my_gst_element_set_state(GstElement *element, GstState state) {
    GstStateChangeReturn ret = orig_gst_element_set_state(element, state);

    if (saved_pipeline == NULL && GST_IS_PIPELINE(element)) {
        saved_pipeline = element;
        DBG("my_gst_element_set_state: saved pipeline from element %p", element);
    }

    if (state == GST_STATE_PLAYING && saved_pipeline != NULL && !pipeline_dumped) {
        pipeline_dumped = true;

        DBG("my_gst_element_set_state: Pipeline %p goes to PLAYING. Dumping .dot data", saved_pipeline);

        gchar *dot_data = gst_debug_bin_to_dot_data(GST_BIN(saved_pipeline), GST_DEBUG_GRAPH_SHOW_ALL);
        if (dot_data) {
            FILE *fp = fopen(dot_path, "w");
            if (fp) {
                fputs(dot_data, fp);
                fclose(fp);
                INFO("my_gst_element_set_state: Pipeline dot data written to %s", dot_path);
            } else {
                ERR("my_gst_element_set_state: Could not open file %s for writing", dot_path);
            }
            g_free(dot_data);
        } else {
            ERR("my_gst_element_set_state: gst_debug_bin_to_dot_data returned NULL");
        }
    }

    return ret;
}


void installHooks(){
	void *self = dlopen(NULL, RTLD_NOW);
	if(self == NULL){
		ERR("dlopen failed: %s", LIB_ERROR());
		return;
	}

    void *p = dlsym(self, "gst_element_set_state");
    if (p == NULL) {
        ERR("installHooks:dlsym error for gst_element_set_state: %s", LIB_ERROR());
    } else {
        orig_gst_element_set_state = (gst_element_set_state_t)inj_backup_function(p, NULL, -1);
        if (!orig_gst_element_set_state) {
            ERR("installHooks: error for gst_element_set_state");
        } else {
            inj_replace_function(p, my_gst_element_set_state);
            INFO("installHooks: success for gst_element_set_state: %p -> %p", p, my_gst_element_set_state);
        }
    }
}

int lib_loginit(log_config_t *log_cfg){
	return -1;
}

int lib_preinit(struct injcode_user *user){
	user->persist = 1;
	return 0;
}

int lib_main(int argc, char *argv[]){
    printf("redirect stdout and stderr to %s", log_path);

    FILE *log_fp = freopen(log_path, "a", stdout);
    if (!log_fp) {
        ERR("lib_main: error while redirecting stdout");
    }

    FILE *err_fp = freopen(log_path, "a", stderr);
    if (!err_fp) {
        ERR("lib_main: error while redirecting stderr");
    }

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	#ifdef USE_LH
	installHooks();
	#endif
	return 0;
}
