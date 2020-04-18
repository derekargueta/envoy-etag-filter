#pragma once

#include <string>
#include <vector>

#include "extensions/filters/http/common/pass_through_filter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Etag {

enum class EtagType { None, IfNoneMatch, IfMatch };

class Filter : public Http::PassThroughFilter {
public:
  Filter() = default;
  ~Filter() = default;

  void onDestroy() override {}

  Http::FilterHeadersStatus decodeHeaders(Http::RequestHeaderMap& headers, bool) override;

  Http::FilterHeadersStatus encodeHeaders(Http::ResponseHeaderMap& headers, bool) override;
  Http::FilterDataStatus encodeData(Buffer::Instance&, bool) override;

private:
  EtagType type_{EtagType::None};

  static const Http::LowerCaseString if_none_match_;
  static const Http::LowerCaseString if_match_;
  static const Http::LowerCaseString etag_;

  std::vector<std::string> etag_values_{};
  bool match_found_{false};

  bool shouldSendResponseBody(absl::string_view upstream_etag);
};

} // Etag
} // HttpFilters
} // Extensions
} // Envoy
