#pragma once

#define LOG_LEVEL_DISABLE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4

#define LOG_LEVEL LOG_LEVEL_DEBUG

#if LOG_LEVEL >= LOG_LEVEL_ERROR

#define init_log(baudrate) (Serial.begin(baudrate))

#define error_logf(format, args...) (Serial.printf(format, args))
#define error_log(arg) (Serial.print(arg))
#define error_logln(arg) (Serial.println(arg))

#else

#define init_log(baudrate)

#define error_logf(format, args...)
#define error_log(arg)
#define error_logln(arg)

#endif

#if LOG_LEVEL >= LOG_LEVEL_WARNING

#define warning_logf(format, args...) (Serial.printf(format, args))
#define warning_log(arg) (Serial.print(arg))
#define warning_logln(arg) (Serial.println(arg))

#else

#define warning_logf(format, args...)
#define warning_log(arg) (Serial.print(arg))
#define warning_logln(arg)

#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO

#define info_logf(format, args...) (Serial.printf(format, args))
#define info_log(arg) (Serial.print(arg))
#define info_logln(arg) (Serial.println(arg))

#else

#define info_logf(format, args...)
#define info_log(arg) (Serial.print(arg))
#define info_logln(arg)

#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG

#define debug_logf(format, args...) (Serial.printf(format, args))
#define debug_log(arg) (Serial.print(arg))
#define debug_logln(arg) (Serial.println(arg))

#else

#define debug_logf(format, args...)
#define debug_log(arg) (Serial.print(arg))
#define debug_logln(arg)

#endif