#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace sm2235 {

class SM2235;

class SM2235Channel : public output::FloatOutput {
 public:
  void set_channel(uint8_t channel) { channel_ = channel; }
  void set_parent(SM2235 *parent) { parent_ = parent; }

 protected:
  void write_state(float state) override;

  uint8_t channel_;
  SM2235 *parent_;
};

class SM2235 : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void set_sda_pin(InternalGPIOPin *pin) { this->sda_pin_ = pin; }
  void set_scl_pin(InternalGPIOPin *pin) { this->scl_pin_ = pin; }

  void register_channel(SM2235Channel *channel, uint8_t num);
  void set_currents(uint8_t currents) { this->currents_ = currents; }

  void set_channel_value(uint8_t channel, uint16_t value);

 protected:
  uint8_t currents_;
  uint8_t num_channels_{0};
  uint16_t values_[5] = {0};
  InternalGPIOPin *sda_pin_;
  InternalGPIOPin *scl_pin_;

  void start_();
  void stop_();
  void send_byte_(uint8_t value);
  void update_(uint8_t channel);
};

}  // namespace sm2235
}  // namespace esphome
