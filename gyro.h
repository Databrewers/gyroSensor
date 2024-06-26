#define ADDRESS_SMPLRT_DIV 0x19    //샘플링 레이트 설정 -> 자이로 4Hz ~ 8kHz, 가속도 4Hz ~ 1kHz
#define ADDRESS_GYRO_CONFIG 0x1B   //자이로 스코프 측정범위 설정
#define ADDRESS_ACCEL_CONFIG 0x1C  //엑셀로미터 측정범위 설정
#define ADDRESS_PWR_MGMT_1 0x6B    //초기 값 0x40, 파워 모드 설정

/*가속도 값 저장되는 레지스터*/
#define ADDRESS_ACCEL_XOUT_H 0x3B  //ACCEL_XOUT[15:8]
#define ADDRESS_ACCEL_XOUT_L 0x3C  //ACCEL_XOUT[7:0]
#define ADDRESS_ACCEL_YOUT_H 0x3D  //ACCEL_YOUT[15:8]
#define ADDRESS_ACCEL_YOUT_L 0x3E  //ACCEL_YOUT[7:0]
#define ADDRESS_ACCEL_ZOUT_H 0x3F  //ACCEL_ZOUT[15:8]
#define ADDRESS_ACCEL_ZOUT_L 0x40  //ACCEL_ZOUT[7:0]

/*각속도 값 저장되는 레지스터*/
#define ADDRESS_GYRO_XOUT_H 0x43  //GYRO_XOUT[15:8]
#define ADDRESS_GYRO_XOUT_L 0x44  //GYRO_XOUT[7:0]
#define ADDRESS_GYRO_YOUT_H 0x45  //GYRO_YOUT[15:8]
#define ADDRESS_GYRO_YOUT_L 0x46  //GYRO_YOUT[7:0]
#define ADDRESS_GYRO_ZOUT_H 0x47  //GYRO_ZOUT[15:8]
#define ADDRESS_GYRO_ZOUT_L 0x48  //GYRO_ZOUT[7:0]

typedef struct //센서값과 단위변환 인자를 멤버로 갖는 구조체
{	
    //raw data에서 다른 단위로 바꿔주는 인자
	//(raw data) / (factor) -> 단위 변환
	float gyro_change_unit_factor; //raw data -> deg/sec
	float accel_change_unit_factor; //raw data -> g (중력가속도)

	//read_gyro, read_accel 함수를 사용하면 값이 업데이트 됨
	int16_t gy_x;	 //센서 raw data 저장되는 변수
	int16_t gy_y;
	int16_t gy_z;
	int16_t ac_x;
	int16_t ac_y;
	int16_t ac_z;
        
    float gy_x_dps; //단위가 deg/sec 일때, 센서 값 저장되는 변수
    float gy_y_dps;
    float gy_z_dps;
        
    float ac_x_g;   //단위가 중력 가속도 일때, 센서 값 저장되는 변수
    float ac_y_g;
    float ac_z_g;
	
}mpu6050;


typedef enum //센서 값 단위 종류
{
    raw_data = 0x00, // 16비트 -32768 ~ 32767
    deg_per_sec = 0x01, //1초 당 움직인 각도
    gravity_acceleration = 0x02 //중력 가속도
          
}unit;



typedef enum //자이로 측정 가능한 범위 종류
{
	gyro_full_scale_range_250 = 0x00,  //±250 deg/sec
	gyro_full_scale_range_500 = 0x01,  //±500 deg/sec
	gyro_full_scale_range_1000 = 0x02, //±1000 deg/sec
	gyro_full_scale_range_2000 = 0x03, //±2000 deg/sec

}gyro_full_scale_range;

typedef enum //가속도 측정 가능한 범위 종류
{
	accel_full_scale_range_2g = 0x00,  //±2g (단위 : 중력가속도)
	accel_full_scale_range_4g = 0x01,  //±4g
	accel_full_scale_range_8g = 0x02,  //±8g
	accel_full_scale_range_16g = 0x03  //±16g

}accel_full_scale_range;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void WHO_AM_I(I2C_HandleTypeDef* hi2c);
void wake_up(I2C_HandleTypeDef* hi2c);
void set_sample_rate(I2C_HandleTypeDef* hi2c2, uint16_t rate); //sample rate 1000Hz로 설정
void set_sensitivity(I2C_HandleTypeDef* hi2c, mpu6050* __my_mpu6050, gyro_full_scale_range gyro_range_you_want, accel_full_scale_range accel_range_you_want);
void read_gyro(I2C_HandleTypeDef* hi2c, mpu6050* __my_mpu6050, unit unit_you_want);
void read_accel( I2C_HandleTypeDef* hi2c,  mpu6050* __my_mpu6050, unit unit_you_want);

