#pragma once

#include <string>
#include <vector>

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

enum EtagType { None, IfNoneMatch, IfMatch };

class EtagFilter : public StreamFilter {
public:
  EtagFilter() {}
  ~EtagFilter() {}

  void onDestroy() override {}

  FilterHeadersStatus decodeHeaders(HeaderMap& headers, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) override;

  FilterHeadersStatus encodeHeaders(HeaderMap& headers, bool) override;
  FilterDataStatus encodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus encodeTrailers(HeaderMap&) override;
  FilterHeadersStatus encode100ContinueHeaders(HeaderMap&) override {
    return FilterHeadersStatus::Continue;
  }
  void setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) override;

private:
  StreamDecoderFilterCallbacks* decoder_callbacks_{};
  StreamEncoderFilterCallbacks* encoder_callbacks_{};
  EtagType type_{None};

  static const LowerCaseString if_none_match_;
  static const LowerCaseString if_match_;
  static const LowerCaseString etag_;

  std::vector<std::string> etag_values_{};
  bool match_found_{false};

  bool shouldSendResponseBody(const std::string upstream_etag);
};

} // Http
} // Envoy
