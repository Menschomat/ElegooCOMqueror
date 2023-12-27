## Elegoo COMqueror - JSON-Based Serial-Interface for Elegoo Conqueror

### Integrated Functions:

#### Input

- closed-loop movement (via gyro)
- direction control
- speed control
- led control

#### Output

- battery volatge data
- distance sensor data

### Integration planed:

- line-tracking senor data
- ir control
- turret movements (servo control)
- gyro sensor data

### Examples

#### Input

| ID  | Direction     |
| --- | ------------- |
| 0   | Forward       |
| 1   | Backward      |
| 2   | Right         |
| 3   | Left          |
| 4   | LeftForward   |
| 5   | LeftBackward  |
| 6   | RightForward  |
| 7   | RightBackward |
| 8   | stop_it       |

```json
{
  "pan": 100,
  "tilt": 100
}
```

#### Output

* distance - ultrasonic-sensor measurement in cm
* voltage - battery-voltage in v

```json
{
  "distance": 10,
  "voltage": 8
}
```
