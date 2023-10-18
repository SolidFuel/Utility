template <class FT> class Glider {
public :
    Glider() : samples_(0) {}
    Glider(FT startValue, FT targetValue, long samples ) {
        restart(startValue, targetValue, samples);

    }

    void restart(FT startValue, FT targetValue, long samples) {
        samples_ = samples;
        delta_ = (targetValue - startValue) / samples;
        latestValue_ = startValue;
    }

    bool in_progress() const {
        return samples_ > 0;
    }

    FT nextValue() { 
        latestValue_ += (delta_ * in_progress() );
        --samples_;
        return latestValue_;
    }

    void stop() { samples_ = 0; }

    void forceValue(FT value) {
        stop();
        latestValue_ = value;
    }

    FT currentValue() const { return latestValue_; }

private :
    long samples_;
    FT delta_;
    FT latestValue_;
};


template <class FT> class BooleanGlider {
public:
    BooleanGlider() {
        glider_.forceValue(falseValue_);
    }

    BooleanGlider(FT falseValue, FT trueValue, long samples ) :
            falseValue_{falseValue},
            trueValue_{trueValue},
            steps_{samples}
    {
        glider_.forceValue(falseValue_);
    }

    void forceValue(bool v) {
        currentBoolValue_ = v;
        stop();
    }

    void stop() { 
        glider_.forceValue(currentBoolValue_ ? trueValue_ : falseValue_ );
    }

    void go(bool value) {
        if (value != currentBoolValue_) {
            glider_.restart(glider_.currentValue(),  value ? trueValue_ : falseValue_, steps_);
            currentBoolValue_ = value;
        }
    }

    FT nextValue() { return glider_.nextValue(); }
    FT currentValue() const { return glider_.currentValue(); }

    bool in_process() const { return glider_.in_progress(); }


private:
    Glider<FT> glider_;
    FT falseValue_ { 0 };
    FT trueValue_ { 1 };
    bool currentBoolValue_ = false;
    long steps_;


};