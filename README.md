## Elegoo COMqueror - JSON-Based Serial-Interface for Elegoo Conqueror

### Integrated Functions:

- closed-loop movement (via gyro)
- direction control
- speed control
- led control

### Integration planed:

- distance sensor data
- line-tracking senor data
- battery volatge data
- ir control
- turret movements (servo control)
- gyro sensor data

### Examples

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
  "direction": 0,
  "speed": 128,
  "color": "#00FFFF"
}
```
