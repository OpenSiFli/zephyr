#ifndef ZEPHYR_SOC_ARM_SIFLI_SFLB32_COMMON_PINCTRL_SOC_H_
#define ZEPHYR_SOC_ARM_SIFLI_SFLB32_COMMON_PINCTRL_SOC_H_

#include <zephyr/dt-bindings/pinctrl/sf32lb-pinctrl.h>

typedef struct pinctrl_soc_pin {
	uint32_t pinmux;
	uint32_t pincfg;
} pinctrl_soc_pin_t;

#define Z_PINCTRL_SF32LB_PINMUX_INIT(node_id, prop, idx) DT_PROP_BY_IDX(node_id, prop, idx)

#define Z_PINCTRL_SF32LB_PINCFG_INIT(node)                                                        \
	((DT_PROP_OR(node, input_enable, 0) << SF32LB_INPUT_ENABLE_POS) |                         \
	 (DT_PROP_OR(node, output_enable, 0) << SF32LB_OUTPUT_ENABLE_POS) |                       \
	 (DT_PROP_OR(node, bias_pull_up, 0) << SF32LB_BIAS_PULL_UP_POS) |                         \
	 (DT_PROP_OR(node, bias_pull_down, 0) << SF32LB_BIAS_PULL_DOWN_POS) |                     \
	 (DT_PROP_OR(node, power_source, 0) << SF32_OUTPUT_HIGH_POS))

/**
 * @brief Utility macro to initialize each pin.
 *
 * @param node_id Node identifier.
 * @param prop Property name.
 * @param idx Property entry index.
 */
#define Z_PINCTRL_STATE_PIN_INIT(node_id, prop, idx)                                           \
	{                                                                                      \
		.pinmux = Z_PINCTRL_SF32LB_PINMUX_INIT(node_id, prop, idx),    \
		.pincfg = Z_PINCTRL_SF32LB_PINCFG_INIT(node_id)     \
	},


/**
 * @brief Utility macro to initialize state pins contained in a given property.
 *
 * @param node_id Node identifier.
 * @param prop Property name describing state pins.
 */
#define Z_PINCTRL_STATE_PINS_INIT(node_id, prop)                                                   \
	{                                                                                          \
		DT_FOREACH_CHILD_VARGS(DT_PHANDLE(node_id, prop), DT_FOREACH_PROP_ELEM, pinmux,    \
				       Z_PINCTRL_STATE_PIN_INIT) \
	}

#endif /* ZEPHYR_SOC_ARM_SIFLI_SF32LB_COMMON_PINCTRL_SOC_H_ */