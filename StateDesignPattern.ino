//Event types
enum EventType {OnClickPause, OnClickWater, OnClickFoam, OnClick3, OnPay, OnTimeElapse};

//States
const int Paused = 0;
const int Waterring = 1;
const int Foaming = 2;
const int Clicking3 = 3;


//function pointer type
typedef int (* pEventHandler)(EventType);

pEventHandler Handlers[4];

bool isPaid;
bool timeElapsed;
int currentState;
EventType eventType;

void setup() 
{
  isPaid = false;
  timeElapsed = true;
  currentState = Paused;
  
  Handlers[0] = PausedStateEventHandler;
  Handlers[1] = WaterringStateEventHandler;
  Handlers[2] = FoamingStateEventHandler;
  Handlers[3] = Click3StateEventHandler;
}

void loop() 
{
  while(true)
  {
    currentState = Handlers[currentState](eventType);
  }
}

int PausedStateEventHandler(EventType eventType)
{
  int result = currentState;
  
  switch(eventType)
  {
    case OnClickWater: {
            if(isPaid)
            {
              result = Waterring;
              ActionWatering();
            }
          } 
          break;
    case OnClickFoam: {
            if(isPaid) 
            {
              result = Foaming;
              ActionFoaming();
            }
          } 
          break;
    case OnClick3: {
            if(isPaid) 
            {
              result = Clicking3;
              ActionClick3();
            }
          } 
          break;
    case OnPay: {
            isPaid = true;
            timeElapsed = false;
          } 
          break;
  }

  return result;
}

int WaterringStateEventHandler(EventType eventType)
{
  int result = currentState;
  
  switch(eventType)
  {
    case OnClickPause: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
    case OnTimeElapse: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
  }

  return result;
}


int FoamingStateEventHandler(EventType eventType)
{
  int result = currentState;
  
  switch(eventType)
  {
    case OnClickPause: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
    case OnTimeElapse: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
  }

  return result;
}

int Click3StateEventHandler(EventType eventType)
{
  int result = currentState;
  
  switch(eventType)
  {
    case OnClickPause: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
    case OnTimeElapse: {
            ActionPause(eventType);
            result = Paused;
          } 
          break;
  }

  return result;
}

//
void ActionPause(EventType eventType)
{
}

void ActionWatering()
{
}

void ActionFoaming()
{
}

void ActionClick3()
{
}
