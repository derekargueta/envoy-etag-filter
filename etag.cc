#include <string>
#include <iostream>

#include "etag.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

///////////////// constructors /////////////////////////////////////////////

EtagFilter::EtagFilter() {}
///////////////////////////////////////////////////////////////////////////////

EtagFilter::~EtagFilter() {}

void EtagFilter::onDestroy() {}

FilterHeadersStatus EtagFilter::decodeHeaders(HeaderMap& headers, bool) {
  auto etag_entry = headers.get(LowerCaseString("etag"));
  if (etag_entry != nullptr) {
    etag_value_ = std::string(etag_entry->value().c_str());
  }

  return FilterHeadersStatus::Continue;
}

FilterDataStatus EtagFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus EtagFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}
void EtagFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

FilterHeadersStatus EtagFilter::encodeHeaders(HeaderMap& headers, bool) {
  auto etag_entry = headers.get(LowerCaseString("etag"));
  if (etag_entry != nullptr) {
    std::string upstream_etag(etag_entry->value().c_str());
    if (upstream_etag == etag_value_) {
      std::cout << "WE GOT A MATCH" << std::endl;
      // TODO update the response and remove the body
    }
  }
  return FilterHeadersStatus::Continue;
}

FilterDataStatus EtagFilter::encodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus EtagFilter::encodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}
void EtagFilter::setEncoderFilterCallbacks(StreamEncoderFilterCallbacks& callbacks) {
  encoder_callbacks_ = &callbacks;
}

} // Http
} // Envoy