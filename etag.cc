#include "etag.h"

#include <string>

#include "absl/strings/str_split.h"
#include "source/common/common/enum_to_int.h"
#include "source/common/http/headers.h"
#include "envoy/http/codes.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Etag {

const Http::LowerCaseString Filter::if_none_match_("if-none-match");
const Http::LowerCaseString Filter::if_match_("if-match");
const Http::LowerCaseString Filter::etag_("etag");

bool Filter::shouldSendResponseBody(absl::string_view upstream_etag) {
  for (const std::string& val : etag_values_) {
    const bool match_any_etag = val == "*";
    const bool etags_match = upstream_etag == val || match_any_etag;

    if (!etags_match) {
      continue;
    } else {
      return type_ != EtagType::IfNoneMatch;
    }
  }

  return type_ == EtagType::IfNoneMatch;
}

// TODO(dereka): what is the specification if a client sents both headers?
// currently chooses if-match
Http::FilterHeadersStatus Filter::decodeHeaders(Http::RequestHeaderMap& headers, bool) {
  auto if_none_match_header = headers.get(if_none_match_);
  if (!if_none_match_header.empty()) {
    type_ = EtagType::IfNoneMatch;
    const absl::string_view etag_value = if_none_match_header[0]->value().getStringView();
    etag_values_ = absl::StrSplit(etag_value, ", ");
  }

  auto if_match_header = headers.get(if_match_);
  if (!if_match_header.empty()) {
    type_ = EtagType::IfMatch;
    const absl::string_view etag_value = if_match_header[0]->value().getStringView();
    etag_values_ = absl::StrSplit(etag_value, ", ");
  }

  return Http::FilterHeadersStatus::Continue;
}

Http::FilterHeadersStatus Filter::encodeHeaders(Http::ResponseHeaderMap& headers, bool) {
  auto etag_entry = headers.get(etag_);
  if (!etag_entry.empty()) {

    const absl::string_view upstream_etag = etag_entry[0]->value().getStringView();
    if (!shouldSendResponseBody(upstream_etag)) {
      match_found_ = true;
      headers.remove(Http::Headers::get().ContentLength);
      headers.addCopy(Http::Headers::get().ContentLength, "0");

      const std::string status = std::to_string(enumToInt(Http::Code::NotModified));
      headers.remove(Http::Headers::get().Status);
      headers.addCopy(Http::Headers::get().Status, status);
    }
  }
  return Http::FilterHeadersStatus::Continue;
}

Http::FilterDataStatus Filter::encodeData(Buffer::Instance& buffer, bool) {
  if (match_found_) {
    buffer.drain(buffer.length());
  }
  return Http::FilterDataStatus::Continue;
}

} // Etag
} // HttpFilters
} // Extensions
} // Envoy
