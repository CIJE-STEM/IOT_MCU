# Walkthrough of Writing and Retrieving Data from Server
## IMPORTANT WARNING
This interface is not intended to be used for sensitive data. This is a CIJE-wide interface. Any data that should be considered private should not be used. 

## Description of the Interface
- Helper functions etc
- The format for a measurement
    1. **timestamp** (required): The date and time of the measurement. XXXX helper function will do all of the work of keeping device clock synced to NTP servers (that is, you device will have the correct global time). Time format is in standard MySQL format of XXXXX
    2. **measurement_value** (required): The numeric (e.g. temperature) or text (e.g. GPS coordinates) value of the measurement. XXXX helper function
    3. **measurement_units** (required): The units of the measurement. XXXX helper function
    4. **measurement_type** (required): Type of measurement, set by the user. It usually will be the type of data, but can be set by user to be more descriptive. For example, you may be measuring the voltage of a battery and the voltage of a light sensor. You can use this to help distinguish between different voltage measurements.
    4. **mac_addr** (required): MAC Address to help identify the specific chip. Typically set for the user directly. User does have access to MAC Address spoofing. XXXXX
    5. ip_address: This is not set by the user. Will be set by the server. Feature still in testing
    6. **device_id** (required): A **user-set** ID. *This is the primaray means of retrieving your data*. **make sure to use a unique ID**. Don't use something like "device1". Set with the helper function XXXXX
    7. **note** (optional): Any additional info that you may want to help identify the information in the future. A good rule is that you will forget everything within two weeks :-). Size limit XXXX. Set with helper function XXXXX

## Example Walkthrough Project

The example project will send the data for a light sensor to our database. We will then retrieve this data with the REST API and XXXX.


## Using General Interface
- Step 1: Develop Local Device and Make Sure data makes sense, etc (XXXX). Do not worry about connecting to server at this stage. 
    - Test sensors and outputs via Serial monitor, voltmeter, or oscilloscope before adding any internet related code. 
    - XXX HERE DO the ADC STUFF
- Step 2: Set up code to get data in the right format for our API. The details of the API format are described above in the section "Description of the Interface" 
    - There is example code in the Arduino library for this. Primarily 
- Step 3: Build out connections to the internet and write to server
    - XXXX A BLOCK DIAGRAM 
        - a simple version where connect directly and only once
        - another where there is a check that it is connected and redo if not
- 
    






## Other Avenues/Approaches
- Azure/AWS IoT Solutions
- Adafruit IO Solutions