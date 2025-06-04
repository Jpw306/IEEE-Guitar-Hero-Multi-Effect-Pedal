// Defining Effect class as a wrapper for all effects
// make reverb its own thing that happens at the end of the chain 


class Effect
{
    public:
        virtual void Initialize(float sample_rate, int mode) {};
        virtual float Process(float inputL, float inputR, float *outL, float *outR) = 0;
        virtual const char *GetName() const = 0;
        virtual int GetID() const = 0;
        virtual ~Effect() {}
        bool active = false;
        void setMode(int value);
        int getMode();
    private:
        int mode;

};

