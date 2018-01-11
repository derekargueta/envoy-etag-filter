#include <string>

#include "etag.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

///////////////// constructors /////////////////////////////////////////////

EtagFilter::EtagFilter() {}
///////////////////////////////////////////////////////////////////////////////

EtagFilter::~EtagFilter() {}

void EtagFilter::onDestroy() {}

FilterHeadersStatus EtagFilter::decodeHeaders(HeaderMap&, bool) {
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

} // Http
} // Envoy