#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : stream("")
    , buffer_max_size(capacity)
    , buffer_current_size(0)
    , buffer_received_size(0)
    , buffer_sent_size(0)
    , _input_ended(false) {}

size_t ByteStream::write(const string &data) {
    size_t data_size = data.size();
    if (data_size + buffer_size() > buffer_max_size) {
        data_size = buffer_max_size - buffer_size();
    }
    stream.append(data.begin(), data.begin() + data_size);
    buffer_current_size += data_size;
    buffer_received_size += data_size;
    return data_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t output_size = min(len, buffer_current_size);
    string output(stream.begin(), stream.begin() + output_size);
    return output;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t output_size = min(len, buffer_current_size);
    stream.erase(0, output_size);
    buffer_current_size -= output_size;
    buffer_sent_size += output_size;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string response = peek_output(len);
    pop_output(len);
    return response;
}

void ByteStream::end_input() { _input_ended = true; }

bool ByteStream::input_ended() const { return _input_ended; }

size_t ByteStream::buffer_size() const { return buffer_current_size; }

bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return buffer_received_size; }

size_t ByteStream::bytes_read() const { return buffer_sent_size; }

size_t ByteStream::remaining_capacity() const { return buffer_max_size - buffer_size(); }
