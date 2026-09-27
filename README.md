# Zephyr Thread and Workqueue Example

A small Zephyr application for the nRF54L15 DK that demonstrates periodic GPIO work using both threads and delayed work items.

## Behavior

- LED 0 is toggled by a dedicated thread every 500 ms.
- LED 1 is toggled by a dedicated thread every 1000 ms.
- LED 2 is toggled by a delayed work item every 250 ms.
- LED 3 is toggled by a delayed work item every 750 ms.

The application uses the `led0` through `led3` devicetree aliases. It exits early if any LED GPIO device is not ready.

## Requirements

- nRF Connect SDK v3.4.0 with its toolchain environment initialized
- The nRF54L15 DK, connected to a supported debug probe for flashing

## Build

From the application directory in an nRF Connect SDK terminal, run:

```sh
west build --build-dir build_54dk --board nrf54l15dk/nrf54l15/cpuapp .
```

To reconfigure from a clean build directory, add `--pristine`:

```sh
west build --build-dir build_54dk --pristine --board nrf54l15dk/nrf54l15/cpuapp .
```

## Flash

With the board connected, run:

```sh
west flash --build-dir build_54dk
```

## Configuration

`prj.conf` sets `CONFIG_STACK_SIZE` to 512 bytes and `CONFIG_PRIORITY` to 5. These application-defined Kconfig options control the two LED thread stacks and their priority; lower Zephyr priority numbers indicate higher priority.