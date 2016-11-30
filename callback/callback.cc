#include <nan.h>
#ifndef _WIN32
# include <unistd.h>
#endif

using namespace v8;
class MyWorker : public Nan::AsyncWorker {
public:
  // Constructor
  MyWorker(Nan::Callback *callback, int delay)
    : Nan::AsyncWorker(callback), delay(delay) {}
  // Destructor
  ~MyWorker() {}
  
  void Execute () {
#ifdef _WIN32
    Sleep(delay);
#else
    usleep(delay * 1000);
#endif
  }

 void HandleOKCallback () {
    Nan::HandleScope scope;
    callback->Call(0, NULL);
  }

private:
  int delay;
};


NAN_METHOD(Delay) {
  Nan::Maybe<int> sec = Nan::To<int>(info[0]);
  int s = sec.FromJust();
  v8::Local<Function> callback = info[1].As<Function>();
  Nan::Callback* nanCallback = new Nan::Callback(callback);

  MyWorker* mw = new MyWorker(nanCallback, s);
  Nan::AsyncQueueWorker(mw);
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("delay").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(Delay)).ToLocalChecked());
}
NODE_MODULE(callback, Init)
