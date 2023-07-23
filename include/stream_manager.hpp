#ifndef STD_STREAM_H
#define STD_STREAM_H

#include <iostream>

class StreamManager {
   public:
    StreamManager(std::istream& in, std::ostream& out, std::ostream& err)
        : in_(in), out_(out), err_(err) {}

    StreamManager(const StreamManager&) = delete;
    StreamManager& operator=(const StreamManager&) = delete;

    inline std::istream& in() { return in_; }

    inline std::ostream& out() { return out_; }

    inline std::ostream& err() { return err_; }

    inline StreamManager redirect_in(std::istream& target) {
        return StreamManager(target, out_, err_);
    }

    inline StreamManager redirect_out(std::ostream& target) {
        return StreamManager(in_, target, err_);
    }

    inline StreamManager redirect_err(std::ostream& target) {
        return StreamManager(in_, out_, target);
    }

   private:
    std::istream& in_;
    std::ostream& out_;
    std::ostream& err_;
};

#endif
