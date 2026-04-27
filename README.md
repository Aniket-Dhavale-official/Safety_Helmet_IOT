ARDUINO UNO (MICROCONTROLLER UNIT)

| Parameter                           | Details                                                                                                                                                                            |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Acts as the main controller to read sensor data, process logic, and control outputs (relay, LED, GSM, etc.)                                                                        |
| **Working**                         | Based on ATmega328P microcontroller. Executes programmed instructions: reads inputs (IR, MQ3, MPU6050), processes conditions, and sends outputs (relay control, LED, GSM commands) |
| **Alternative**                     | ESP32 (WiFi + Bluetooth), Arduino Nano (compact), Raspberry Pi (advanced processing), STM32                                                                                        |
| **Purpose (Why this board?)**       | Easy to program, widely supported, sufficient I/O pins, ideal for prototyping and academic projects                                                                                |
| **Total Cost (Board)**              | ₹300 – ₹500                                                                                                                                                                        |
| **Real-Life Placement**             | Inside a protected enclosure on bike (under seat or dashboard unit)                                                                                                                |
| **Real-Life Issues / Flaws**        | Not rugged (not automotive-grade); limited memory and processing power; sensitive to vibration, heat, and moisture                                                                 |
| **Production-Level Fix**            | Replace with **automotive-grade MCU (ESP32/STM32)**; use PCB instead of breadboard; add casing (waterproof, vibration-proof)                                                       |
| **Connections**                     | Digital pins (D2–D13) → sensors/relay/LED • Analog pins (A0) → MQ3 • I2C (A4 SDA, A5 SCL) → MPU6050/LCD • UART (D10–D11 via SoftwareSerial) → GSM/GPS                              |
| **Input / Output Type**             | Input: Digital & Analog signals • Output: Digital signals, Serial communication (UART/I2C)                                                                                         |
| **Accuracy (Practical)**            | ~95–99% reliable processing (depends on sensor accuracy, not controller)                                                                                                           |
| **Project-Level Cost Impact**       | ~₹400 (major core component in total ~₹1800–₹2200 project cost)                                                                                                                    |
| **Role in Overall Project Working** | Central brain → integrates all sensors, applies logic, controls ignition and communication modules                                                                                 |
| **System Requirement Contribution** | Enables automation, decision-making, and coordination between all modules                                                                                                          |
| **Project Working (with Arduino)**  | Reads helmet → reads alcohol → monitors MPU6050 → if unsafe → relay OFF; if accident → triggers GSM + GPS; controls LED/LCD accordingly                                            |
| **Requirements**                    | Stable power supply, proper pin configuration, uploaded program, grounding across all modules                                                                                      |
| **Limitations**                     | Limited RAM/Flash; cannot handle complex AI/processing; lacks built-in connectivity (WiFi/GSM)                                                                                     |


IR SENSOR MODULE (Helmet Detection)

| Parameter                           | Details                                                                                                                                                                                                                    |
| ----------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Detect whether helmet strap is worn (proximity detection)                                                                                                                                                                  |
| **Working**                         | The IR LED emits infrared light and a photodiode/phototransistor receives reflected light. When an object (strap/face) is close, reflection increases → comparator (LM393 inside module) gives **digital LOW/HIGH output** |
| **Alternative**                     | Magnetic reed switch, Hall effect sensor, mechanical push switch (helmet buckle), capacitive proximity sensor                                                                                                              |
| **Purpose (Why this sensor?)**      | Cheap, easy to interface (digital output), no complex processing required, fast response → suitable for prototype-level safety logic                                                                                       |
| **Total Cost (Sensor)**             | ₹30 – ₹80                                                                                                                                                                                                                  |
| **Real-Life Placement**             | Inside helmet near chin strap or locking area so that strap closure changes reflection                                                                                                                                     |
| **Real-Life Issues / Flaws**        | Sensitive to sunlight, dust, and ambient IR; false triggering; alignment issues; can be bypassed easily                                                                                                                    |
| **Production-Level Fix**            | Replace with **magnetic buckle sensor or latch switch**; add shielding; use sensor fusion (combine with motion + pressure); add debounce logic in software                                                                 |
| **Connections**                     | VCC → 5V (Arduino)  • GND → GND  • OUT → Digital Pin (e.g., D2)                                                                                                                                                            |
| **Input / Output Type**             | Input: Infrared reflection  • Output: Digital (HIGH/LOW)                                                                                                                                                                   |
| **Accuracy (Practical)**            | ~70–85% in controlled conditions; drops in sunlight/outdoor environments                                                                                                                                                   |
| **Project-Level Cost Impact**       | ~₹50 (very low contribution to total ~₹1800–₹2200 project cost)                                                                                                                                                            |
| **Role in Overall Project Working** | Step 1 of safety logic → if helmet not detected → relay OFF → ignition blocked                                                                                                                                             |
| **System Requirement Contribution** | Ensures rider compliance before ignition; acts as primary safety gate                                                                                                                                                      |
| **Project Working (with IR)**       | IR checks helmet → if NOT worn → Arduino disables relay → bike won’t start; if worn → system proceeds to alcohol check and other modules                                                                                   |

MQ3 ALCOHOL SENSOR

| Parameter                           | Details                                                                                                                                                                                    |
| ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Use**                             | Detect presence of alcohol in rider’s breath                                                                                                                                               |
| **Working**                         | The sensor contains a **SnO₂ (tin dioxide) sensitive layer** whose resistance changes when exposed to alcohol vapors. This variation is converted into an analog voltage → read by Arduino |
| **Alternative**                     | Fuel cell alcohol sensor (high accuracy), MQ2/MQ135 (less specific), semiconductor breath analyzers                                                                                        |
| **Purpose (Why this sensor?)**      | Low cost, easy analog interfacing, sufficient for **prototype-level alcohol detection**, widely available                                                                                  |
| **Total Cost (Sensor)**             | ₹120 – ₹200                                                                                                                                                                                |
| **Real-Life Placement**             | Inside helmet near mouth/nose region to capture breath directly                                                                                                                            |
| **Real-Life Issues / Flaws**        | Detects perfume, deodorant, smoke; requires warm-up (20–60 sec); sensitivity drift over time; affected by temperature/humidity                                                             |
| **Production-Level Fix**            | Use **fuel-cell based breath analyzer**; add calibration routines; implement filtering + threshold tuning; combine with airflow detection (actual breath confirmation)                     |
| **Connections**                     | VCC → 5V  • GND → GND  • AOUT → A0 (Arduino analog pin)                                                                                                                                    |
| **Input / Output Type**             | Input: Alcohol vapor (gas concentration)  • Output: Analog voltage (0–1023)                                                                                                                |
| **Accuracy (Practical)**            | ~60–75% for raw MQ3; improves with calibration but still not legally reliable                                                                                                              |
| **Project-Level Cost Impact**       | ~₹150 (moderate contribution to total ~₹1800–₹2200 project cost)                                                                                                                           |
| **Role in Overall Project Working** | Step 2 of safety logic → if alcohol detected → relay OFF → ignition blocked                                                                                                                |
| **System Requirement Contribution** | Prevents drunk driving; ensures rider safety compliance                                                                                                                                    |
| **Project Working (with MQ3)**      | After helmet check → MQ3 reads alcohol level → if value > threshold → Arduino disables relay → bike won’t start; else system proceeds normally                                             |


RELAY MODULE (Ignition Control)

| Parameter                                | Details                                                                                                                                                                                                      |
| ---------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Use**                                  | Control bike ignition ON/OFF based on safety conditions                                                                                                                                                      |
| **Working**                              | An electromagnetic coil inside the relay is energized by Arduino → creates magnetic field → switches internal contact from **NO (Normally Open)** to **COM (Common)** → completes or breaks ignition circuit |
| **Alternative**                          | MOSFET (solid-state switching), transistor + relay driver, solid-state relay (SSR)                                                                                                                           |
| **Purpose (Why this sensor/component?)** | Allows **low-power Arduino signal** to control **high-power ignition circuit** safely with electrical isolation                                                                                              |
| **Total Cost (Module)**                  | ₹80 – ₹120                                                                                                                                                                                                   |
| **Real-Life Placement**                  | Installed near bike ignition wiring or inside control box                                                                                                                                                    |
| **Real-Life Issues / Flaws**             | Mechanical wear over time; slower switching; audible clicking; susceptible to vibration; contact sparking                                                                                                    |
| **Production-Level Fix**                 | Replace with **MOSFET or automotive-grade relay**; add flyback diode; use vibration-resistant enclosure                                                                                                      |
| **Connections**                          | IN → D7 (Arduino) • VCC → 5V • GND → GND • COM → ignition line • NO → ignition output                                                                                                                        |
| **Input / Output Type**                  | Input: Digital signal (HIGH/LOW) • Output: Electrical switching (open/close circuit)                                                                                                                         |
| **Accuracy (Practical)**                 | ~95–99% reliable switching (hardware-based, not sensor-dependent)                                                                                                                                            |
| **Project-Level Cost Impact**            | ~₹100 (small contribution to total ~₹1800–₹2200 project cost)                                                                                                                                                |
| **Role in Overall Project Working**      | Final control stage → enables/disables ignition based on helmet + alcohol + accident logic                                                                                                                   |
| **System Requirement Contribution**      | Ensures enforcement of safety rules by physically controlling engine start                                                                                                                                   |
| **Project Working (with Relay)**         | If all conditions safe → Arduino sends HIGH/LOW → relay closes circuit → ignition ON; if unsafe → relay opens → ignition OFF                                                                                 |


MPU6050 (ACCIDENT DETECTION SENSOR)

| Parameter                           | Details                                                                                                                                                                  |
| ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Use**                             | Detect accidents by monitoring sudden changes in motion (acceleration/tilt)                                                                                              |
| **Working**                         | Combines a **3-axis accelerometer + 3-axis gyroscope**. It measures acceleration (ax, ay, az) and angular velocity. Sudden spikes beyond threshold indicate crash/impact |
| **Alternative**                     | ADXL345 (accelerometer), vibration sensor (basic), IMU modules (MPU9250, BNO055 – more advanced)                                                                         |
| **Purpose (Why this sensor?)**      | Provides **multi-axis motion sensing**, better accuracy than simple vibration sensors, compact and widely used in motion-based applications                              |
| **Total Cost (Sensor)**             | ₹150 – ₹250                                                                                                                                                              |
| **Real-Life Placement**             | Mounted firmly on bike chassis/frame (not helmet) for accurate motion detection                                                                                          |
| **Real-Life Issues / Flaws**        | False positives due to potholes, sudden braking; sensitivity to mounting position; noise in readings; requires calibration                                               |
| **Production-Level Fix**            | Use **sensor fusion + filtering algorithms**; combine with speed sensor & GPS; apply threshold smoothing and time-based validation                                       |
| **Connections**                     | VCC → 5V • GND → GND • SDA → A4 • SCL → A5 (I2C communication)                                                                                                           |
| **Input / Output Type**             | Input: Physical motion (acceleration & rotation) • Output: Digital data via I2C (ax, ay, az values)                                                                      |
| **Accuracy (Practical)**            | ~75–90% depending on calibration; raw threshold method is less reliable without filtering                                                                                |
| **Project-Level Cost Impact**       | ~₹200 (moderate contribution to total ~₹1800–₹2200 project cost)                                                                                                         |
| **Role in Overall Project Working** | Continuous monitoring → if sudden impact detected → triggers accident condition → activates GSM alert system                                                             |
| **System Requirement Contribution** | Enables automatic accident detection and emergency response                                                                                                              |
| **Project Working (with MPU6050)**  | Sensor continuously sends motion data → Arduino checks thresholds → if abnormal spike detected → accident flagged → relay OFF + GSM sends alert with location            |
| **Requirements**                    | Proper calibration, stable mounting, I2C communication setup, threshold tuning in code                                                                                   |
| **Limitations**                     | Cannot distinguish all real accidents vs bumps; depends heavily on threshold logic                                                                                       |


LED (STATUS INDICATOR)

| Parameter                           | Details                                                                                                                             |
| ----------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Indicate system status (safe / unsafe / alert conditions)                                                                           |
| **Working**                         | When voltage is applied across the LED (with a current-limiting resistor), electrons recombine and emit light (electroluminescence) |
| **Alternative**                     | Buzzer (audio alert), RGB LED (multi-status), OLED/LCD display, indicator lamps                                                     |
| **Purpose (Why this component?)**   | Simple visual feedback; helps in debugging and demonstration; low cost and easy to interface                                        |
| **Total Cost (Component)**          | ₹5 – ₹20                                                                                                                            |
| **Real-Life Placement**             | On dashboard or visible area near ignition/control panel                                                                            |
| **Real-Life Issues / Flaws**        | Limited visibility in daylight; conveys limited information (single color); not noticeable in bright sunlight                       |
| **Production-Level Fix**            | Use **high-brightness LEDs**, RGB indicators, or combine with buzzer/display for better feedback                                    |
| **Connections**                     | Anode (+) → Arduino digital pin (e.g., D8) through 220Ω resistor • Cathode (–) → GND                                                |
| **Input / Output Type**             | Input: Digital signal (HIGH/LOW) • Output: Visual light indication                                                                  |
| **Accuracy (Practical)**            | ~100% (pure output device, no sensing involved)                                                                                     |
| **Project-Level Cost Impact**       | Negligible (~₹10 contribution to total ~₹1800–₹2200 project cost)                                                                   |
| **Role in Overall Project Working** | Indicates system state: ON = safe to drive; OFF/blinking = unsafe or alert condition                                                |
| **System Requirement Contribution** | Provides immediate visual feedback to user about system decisions                                                                   |
| **Project Working (with LED)**      | Arduino sets HIGH → LED ON (safe condition); LOW → LED OFF (unsafe / alert like helmet missing, alcohol detected, accident)         |
| **Requirements**                    | Proper resistor (≈220Ω) to limit current; correct polarity                                                                          |
| **Limitations**                     | Cannot convey detailed information; requires user attention                                                                         |

GPS MODULE (Location Tracking – NEO-6M)

| Parameter                           | Details                                                                                                                                                                       |
| ----------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Determine real-time geographic location (latitude & longitude) for accident reporting                                                                                         |
| **Working**                         | Receives signals from multiple GPS satellites and uses **trilateration** to calculate position (lat, lon, time). Sends NMEA data (e.g., $GPGGA, $GPRMC) via serial to Arduino |
| **Alternative**                     | Smartphone GPS (app-based), GSM-based location (less accurate), advanced GNSS modules (NEO-M8N, u-blox M10)                                                                   |
| **Purpose (Why this sensor?)**      | Provides **independent, accurate outdoor location** without internet; essential for emergency response in accident detection                                                  |
| **Total Cost (Sensor)**             | ₹250 – ₹350                                                                                                                                                                   |
| **Real-Life Placement**             | Mounted on top side of bike or near dashboard with **clear sky visibility** (antenna facing upward)                                                                           |
| **Real-Life Issues / Flaws**        | No signal indoors/under bridges; slow initial fix (cold start 30–60 sec); may output (0,0) when no lock; affected by buildings/trees                                          |
| **Production-Level Fix**            | Use **high-sensitivity GNSS (multi-constellation GPS+GLONASS)**; add external antenna; cache last known location; integrate with mobile network fallback                      |
| **Connections**                     | VCC → 5V • GND → GND • TX → Arduino RX (e.g., D4) • RX → Arduino TX (e.g., D5)                                                                                                |
| **Input / Output Type**             | Input: Satellite radio signals • Output: Serial data (NMEA strings → parsed to latitude & longitude)                                                                          |
| **Accuracy (Practical)**            | ~2–5 meters (open sky); can degrade to 10–20 m in urban environments                                                                                                          |
| **Project-Level Cost Impact**       | ~₹300 (moderate contribution to total ~₹1800–₹2200 project cost)                                                                                                              |
| **Role in Overall Project Working** | Provides location data during accident → appended to SMS via GSM module                                                                                                       |
| **System Requirement Contribution** | Enables emergency services/family to locate accident spot quickly                                                                                                             |
| **Project Working (with GPS)**      | GPS continuously outputs data → Arduino parses coordinates → if accident occurs → location included in SMS alert                                                              |
| **Requirements**                    | Clear sky view; proper serial communication; time for satellite lock; stable power                                                                                            |
| **Limitations**                     | Cannot work underground/indoors; delay i                                                                                                                                      |


GSM MODULE (SIM800L – Emergency Communication)

| Parameter                           | Details                                                                                                                                        |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Send SMS alerts (with accident location) to predefined phone number                                                                            |
| **Working**                         | Uses cellular network (SIM card). Arduino sends **AT commands** via serial → module processes and sends SMS/calls over GSM network             |
| **Alternative**                     | ESP32 + internet (WiFi), 4G LTE modules (SIM7600), LoRa (long-range but no SMS), mobile app integration                                        |
| **Purpose (Why this module?)**      | Works **without internet**, reliable for emergency messaging, widely available and low cost                                                    |
| **Total Cost (Module)**             | ₹250 – ₹400                                                                                                                                    |
| **Real-Life Placement**             | Inside bike enclosure (under seat/dashboard) with some signal exposure                                                                         |
| **Real-Life Issues / Flaws**        | Requires stable **4V supply with ~2A peak current**; network dependency; signal issues in remote areas; resets if power unstable               |
| **Production-Level Fix**            | Use **regulated power supply (buck converter + battery)**; add bulk capacitor; use 4G modules; implement retry logic and delivery confirmation |
| **Connections**                     | VCC → 4V external battery • GND → GND • TX → Arduino RX (e.g., D10) • RX → Arduino TX (e.g., D11 via voltage drop)                             |
| **Input / Output Type**             | Input: AT commands (serial) • Output: SMS/call over GSM network                                                                                |
| **Accuracy (Practical)**            | ~95% message delivery (depends on network availability)                                                                                        |
| **Project-Level Cost Impact**       | ~₹300 (major component in total ~₹1800–₹2200 project cost)                                                                                     |
| **Role in Overall Project Working** | Emergency module → sends SMS when accident detected                                                                                            |
| **System Requirement Contribution** | Enables real-time communication to emergency contacts                                                                                          |
| **Project Working (with GSM)**      | Accident detected → Arduino fetches GPS → sends AT commands → GSM sends SMS with coordinates                                                   |
| **Requirements**                    | SIM card with balance; stable 4V power (2A peak); antenna/network signal; proper serial communication                                          |
| **Limitations**                     | No operation without network; sensitive to voltage drops; slower compared to internet-based systems                                            |

DC MOTOR (IGNITION / LOAD SIMULATION)

| Parameter                           | Details                                                                                                                                    |
| ----------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| **Use**                             | Simulate bike ignition/engine or act as load controlled by relay (ON/OFF)                                                                  |
| **Working**                         | When DC voltage is applied, current flows through armature → magnetic field interaction produces rotation (electromagnetic principle)      |
| **Alternative**                     | Actual ignition circuit of vehicle, DC fan, bulb (simpler load), solenoid                                                                  |
| **Purpose (Why this component?)**   | Safe way to **demonstrate ignition control** without using a real bike; visually shows system response                                     |
| **Total Cost (Component)**          | ₹80 – ₹200                                                                                                                                 |
| **Real-Life Placement**             | In prototype: breadboard/demo setup; In real system: replaced by actual bike ignition circuit                                              |
| **Real-Life Issues / Flaws**        | Not representative of real ignition load; draws current differently; no real engine behavior; may introduce noise/back-EMF                 |
| **Production-Level Fix**            | Replace with **actual ignition interfacing circuit**; use proper automotive relay/MOSFET driver; add protection components (flyback diode) |
| **Connections**                     | Motor + → Relay NO • Relay COM → Power supply + • Motor – → GND (through power source)                                                     |
| **Input / Output Type**             | Input: Electrical power • Output: Mechanical rotation                                                                                      |
| **Accuracy (Practical)**            | Not applicable (actuator, not sensor); ~100% for demonstrating ON/OFF control                                                              |
| **Project-Level Cost Impact**       | ~₹100 (minor contribution to total ~₹1800–₹2200 project cost)                                                                              |
| **Role in Overall Project Working** | Represents ignition → turns ON only when all safety conditions are satisfied                                                               |
| **System Requirement Contribution** | Demonstrates enforcement of safety logic (engine starts/stops)                                                                             |
| **Project Working (with Motor)**    | If helmet + alcohol conditions satisfied → relay closes → motor rotates (engine ON); else → relay open → motor OFF                         |
| **Requirements**                    | External power supply (if higher voltage motor); relay control; proper wiring                                                              |
| **Limitations**                     | Not real-world accurate; does not reflect actual vehicle ignition complexity                                                               |


LCD DISPLAY (16×2 – USER INTERFACE)

| Parameter                           | Details                                                                                                                                                                                             |
| ----------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Use**                             | Display system status (Helmet status, Alcohol alert, Accident alert, GPS info, etc.)                                                                                                                |
| **Working**                         | Uses liquid crystal cells that change alignment when voltage is applied → characters are displayed via controller (HD44780). Communicates either in **parallel (16 pins)** or **I2C (2-wire)** mode |
| **Alternative**                     | OLED display (better contrast), TFT display, LED indicators, mobile app interface                                                                                                                   |
| **Purpose (Why this component?)**   | Provides **real-time textual feedback** to user; useful for debugging and demonstration                                                                                                             |
| **Total Cost (Component)**          | ₹120 – ₹200 (₹150–₹250 with I2C module)                                                                                                                                                             |
| **Real-Life Placement**             | Mounted on bike dashboard/control panel                                                                                                                                                             |
| **Real-Life Issues / Flaws**        | Poor visibility in sunlight; bulky wiring (parallel mode); slow refresh; fragile                                                                                                                    |
| **Production-Level Fix**            | Replace with **OLED/TFT display**; use sealed automotive display; reduce dependency on display (use mobile app)                                                                                     |
| **Connections (I2C – Recommended)** | VCC → 5V • GND → GND • SDA → A4 • SCL → A5                                                                                                                                                          |
| **Connections (16-pin Parallel)**   | RS → D12 • E → D11 • D4–D7 → D5, D6, D3, D9 • VCC → 5V • GND → GND • RW → GND • V0 → contrast control                                                                                               |
| **Input / Output Type**             | Input: Data/commands from Arduino • Output: Visual text display                                                                                                                                     |
| **Accuracy (Practical)**            | ~100% (output device; depends on correct code and wiring)                                                                                                                                           |
| **Project-Level Cost Impact**       | ~₹150 (moderate contribution to total ~₹1800–₹2200 project cost)                                                                                                                                    |
| **Role in Overall Project Working** | Displays system decisions (SAFE / HELMET MISSING / ALCOHOL DETECTED / ACCIDENT ALERT)                                                                                                               |
| **System Requirement Contribution** | Improves usability and monitoring; helps debugging                                                                                                                                                  |
| **Project Working (with LCD)**      | Arduino processes sensor data → sends text commands → LCD updates display in real-time                                                                                                              |
| **Requirements**                    | Proper wiring; correct I2C address (0x27/0x3F); contrast adjustment (parallel mode)                                                                                                                 |
| **Limitations**                     | Limited characters (16×2); not ideal for bright outdoor conditions                                                                                                                                  |





