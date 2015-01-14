#include "CfgFactionClasses.h"

class CfgVehicles {
  class Logic;
  class Module_F: Logic {
    class ArgumentsBaseUnits {
    };
  };
  class cse_enableLogging: Module_F {
    scope = 2; 
    displayName = "Logging [CSE]";
    icon = "\cse\cse_main\data\cse_logging_icon.paa";
    category = "cseDebug";
    function = "cse_fnc_debugModule";
    functionPriority = 1;
    isGlobal = 1;
    isTriggerActivated = 0;
    class Arguments {
      class logLevel {
        displayName = "Enable Logging at";
        description = "The maximum level of logging"; 
        typeName = "STRING";
        class values {
          class NONE {name="None"; value=4; default=1; };
          class INFO {name="Information"; value=3; };
          class DEBUG {name="Debug"; value=2; };
          class WARN {name="Warnings"; value=1; };
          class ERROR {name="Errors"; value=0; };
        };
      }; 
      class logDisplayLevel {
        displayName = "Show in chat";
        description = "The maximum level of log messages to be shown in chat"; 
        typeName = "STRING";
        class values {
          class NONE {name="None"; value=4; default=1; };
          class INFO {name="Information"; value=3; };
          class DEBUG {name="Debug"; value=2; };
          class WARN {name="Warnings"; value=1; };
          class ERROR {name="Errors"; value=0; };
        };
      };
    };
    class ModuleDescription {
      description = "Lets you modify the logging settings within CSE."; // Short description, will be formatted as structured text
      sync[] = {};
    };
  };
  class cse_traceValuesObject: Module_F {
    
    scope = 2; 
    displayName = "Trace variables [CSE]";
    icon = "\cse\cse_main\data\cse_debug_icon.paa";
    category = "cseDebug";
    function = "cse_fnc_traceModule";
    functionPriority = 1;
    isGlobal = 1;
    isTriggerActivated = 1;
    class Arguments {
      class enableFor {
        displayName = "Trace player variables";
        description = "Whatever or not a debug message will be printed when a value for a player changes"; 
        typeName = "STRING";
        class values {
          class DISABLED {name="Disable"; value=0; default=1; };
          class ENABLE {name="Enable"; value=1; };
        };
      }; 
    };
    class ModuleDescription {
      description = "Trace variables of given object"; // Short description, will be formatted as structured text
      sync[] = {};
    };
  };


  class cse_basicRevive: Module_F {
    scope = 2; 
    displayName = "Basic Revive [CSE]"; 
    icon = "\cse\cse_main\data\cse_medical_module.paa";
    category = "cse_medical";
    function = "cse_fnc_initalizeModule_F";
    functionPriority = 1;
    isGlobal = 1;
    isTriggerActivated = 0;
    class Arguments {
      class enableFor {
        displayName = "Enable for";
        description = "Should the basic revive be enabled for players, AI or both?"; 
        typeName = "NUMBER";
        class values {
          class disable {name="Disable"; value=0; default=1; };
          class playersOnly {name="Players only"; value=1; };
          class playersAndAI { name="Players and AI"; value = 2; };
        };
      };
      class timer {
        displayName = "Timer";
        description = "How long can a unit spend in unconscious mode (In seconds)"; 
        typeName = "NUMBER";
        defaultValue = 600;
      };
      class amountOf {
        displayName = "Hits while unconscious";
        description = "number of times a unit can be hit/killed before being force killed. -1 is disabled."; 
        typeName = "NUMBER";
        defaultValue = -1;
      };
    };
    class ModuleDescription {
      description = "Enables the basic revive script for all damage done through CSE. <br />Any unit that is killed, will be put in an unconscious state until their timer runs out.";
      sync[] = {};
    };
  };
};