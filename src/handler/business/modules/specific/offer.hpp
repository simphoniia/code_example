#pragma once

#include <module_interface.hpp>

namespace modules {

struct OfferStat {
  long long item_id;
  double price;
  long long image_id;
  bool available;
};

class Offer : public Module {
public:
  void ProcessModule(const request::HttpRequest &request);

  const OfferStat &GetOfferStat() const { return stats_; }

private:
  OfferStat stats_;
};

} // namespace modules
