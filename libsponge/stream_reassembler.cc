#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    : _output(capacity)
    , _capacity(capacity)
    , unassembled_streams(std::set<UnassembledStream>())
    , _unassembled_bytes(0)
    , _index_to_read(0) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const std::string &data, const uint64_t index, const bool eof) {
    if (unassembled_bytes() + data.size() > _capacity) {
        return;
    }
    // Add segment to unassembled streams
    unassembled_streams.insert(UnassembledStream(index, data, eof));
    _unassembled_bytes += data.size();

    // assemble stream if it is ready.
    while (!unassembled_streams.empty() && unassembled_streams.begin()->get_index() <= _index_to_read) {
        UnassembledStream stream_to_merge = *unassembled_streams.begin();

        // calculate the intervel to merge.
        size_t start_index = _index_to_read - stream_to_merge.get_index();
        size_t length_to_merge = stream_to_merge.get_size() - start_index;

        _output.write(data.substr(start_index, length_to_merge));

        if (stream_to_merge.is_eof()) {
            unassembled_streams.clear();
            _unassembled_bytes = 0;
            _output.end_input();
        } else {
            unassembled_streams.erase(stream_to_merge);
            _unassembled_bytes -= stream_to_merge.get_size();
            _index_to_read += length_to_merge;
        }
    }
}

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_bytes; }

bool StreamReassembler::empty() const { return unassembled_streams.empty(); }
