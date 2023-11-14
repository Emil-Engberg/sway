#include "sway/commands.h"
#include "sway/config.h"
#include "sway/output.h"
#include "util.h"

struct cmd_results *output_cmd_adaptive_sync(int argc, char **argv) {
	if (!config->handler_context.output_config) {
		return cmd_results_new(CMD_FAILURE, "Missing output config");
	}
	if (argc == 0) {
		return cmd_results_new(CMD_INVALID, "Missing adaptive_sync argument");
	}
	
	int current_value = 1;
	
	if(strcmp(argv[0], "toggle") == 0) {
		struct output_config *oc = config->handler_context.output_config;
		struct sway_output *sway_output = all_output_by_name_or_id(oc->name);
		if (sway_output == NULL) {
			return cmd_results_new(CMD_FAILURE,
				"Cannot apply toggle to unknown output %s", oc->name);
		}
		oc = find_output_config(sway_output);
		
		current_value = !oc || oc->adaptive_sync;
		
		free(oc);
	}
	
	config->handler_context.output_config->adaptive_sync = parse_boolean(argv[0], current_value);
	
	config->handler_context.leftovers.argc = argc - 1;
	config->handler_context.leftovers.argv = argv + 1;
	return NULL;
}
