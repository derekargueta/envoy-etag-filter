#include <sstream>
#include <string>

#include "etag.h"

#include "absl/strings/str_split.h"
#include "common/common/enum_to_int.h"
#include "common/http/headers.h"
#include "envoy/http/codes.h"
#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

const LowerCaseString EtagFilter::if_none_match_("if-none-match");
const LowerCaseString EtagFilter::if_match_("if-match");
const LowerCaseString EtagFilter::etag_("etag");

bool EtagFilter::shouldSendResponseBody(const std::string upstream_etag) {
  for (const std::string& val : etag_values_) {
    bool match_any_etag = val == "*";
    bool etags_match = upstream_etag == val || match_any_etag;

    if (!etags_match) {
      continue;
    } else {
      if (type_ == IfNoneMatch) {
        return false;
      } else {
        return true;
      }
    }
  }

  return type_ == IfNoneMatch;
}

// TODO(dereka): what is the specification if a client sents both headers?
// currently chooses if-match
FilterHeadersStatus EtagFilter::decodeHeaders(HeaderMap& headers, bool) {
  auto if_none_match_header = headers.get(if_none_match_);
  if (if_none_match_header != nullptr) {
    type_ = IfNoneMatch;
    std::string etag_value = std::string(if_none_match_header->value().c_str());
    etag_values_ = absl::StrSplit(etag_value, ", ");
  }

  auto if_match_header = headers.get(if_match_);
  if (if_match_header != nullptr) {
    type_ = IfMatch;
    std::string etag_value = std::string(if_match_header->value().c_str());
    etag_values_ = absl::StrSplit(etag_value, ", ");
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
  auto etag_entry = headers.get(etag_);
  if (etag_entry != nullptr) {

    std::string upstream_etag(etag_entry->value().c_str());
    if (!shouldSendResponseBody(upstream_etag)) {
      match_found_ = true;
      headers.remove(Headers::get().ContentLength);
      headers.addCopy(Headers::get().ContentLength, "0");

      std::string status = std::to_string(enumToInt(Http::Code::NotModified));
      headers.remove(Headers::get().Status);
      headers.addCopy(Headers::get().Status, status);
    }
  }
  return FilterHeadersStatus::Continue;
}

FilterDataStatus EtagFilter::encodeData(Buffer::Instance& buffer, bool) {
  if (match_found_) {
    buffer.drain(buffer.length());
  }
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