import json
import socket
import threading
import time
import urllib.error
import urllib.parse
import urllib.request
from os.path import join

from kivy.app import App
from kivy.clock import Clock
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.properties import NumericProperty, StringProperty
from kivy.storage.jsonstore import JsonStore
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import Screen, ScreenManager, SlideTransition
from kivy.utils import get_color_from_hex

Window.clearcolor = get_color_from_hex("#eef5f7")
Window.softinput_mode = "below_target"

NAMES = ["Morning", "Afternoon", "Night"]
DEFAULT_PORT = 5500

KV = """
<Txt@Label>:
    color: 0.09, 0.2, 0.27, 1
    size_hint_y: None
    height: self.texture_size[1] + dp(6)
    text_size: self.width, None
    halign: 'left'
    valign: 'middle'

<TealButton@Button>:
    background_normal: ''
    background_down: ''
    background_color: 0.03, 0.49, 0.52, 1
    color: 1, 1, 1, 1
    bold: True
    size_hint_y: None
    height: dp(46)

<SoftButton@Button>:
    background_normal: ''
    background_down: ''
    background_color: 0.9, 0.95, 0.96, 1
    color: 0.07, 0.4, 0.42, 1
    bold: True
    size_hint_y: None
    height: dp(46)

<RedButton@Button>:
    background_normal: ''
    background_down: ''
    background_color: 0.79, 0.19, 0.23, 1
    color: 1, 1, 1, 1
    bold: True
    size_hint_y: None
    height: dp(46)

<Card>:
    orientation: 'vertical'
    padding: dp(14)
    spacing: dp(8)
    size_hint_y: None
    height: self.minimum_height
    canvas.before:
        Color:
            rgba: 1, 1, 1, 1
        RoundedRectangle:
            pos: self.pos
            size: self.size
            radius: [dp(14)]

<CompartmentCard>:
    BoxLayout:
        size_hint_y: None
        height: dp(30)
        Txt:
            text: root.title
            bold: True
            font_size: sp(18)
            height: dp(30)
        Txt:
            text: root.state_text
            halign: 'right'
            font_size: sp(13)
            height: dp(30)
    BoxLayout:
        size_hint_y: None
        height: dp(40)
        spacing: dp(8)
        Switch:
            id: enabled_switch
            active: True
            size_hint_x: None
            width: dp(90)
        Txt:
            text: 'Enable daily reminder'
            height: dp(40)
    Txt:
        text: 'Reminder time'
        bold: True
        font_size: sp(14)
    BoxLayout:
        size_hint_y: None
        height: dp(46)
        spacing: dp(6)
        TextInput:
            id: hour_input
            text: '8'
            multiline: False
            input_filter: 'int'
            halign: 'center'
            font_size: sp(20)
            padding: [dp(8), dp(10)]
        Label:
            text: ':'
            color: 0.09, 0.2, 0.27, 1
            size_hint_x: None
            width: dp(12)
            font_size: sp(22)
        TextInput:
            id: minute_input
            text: '00'
            multiline: False
            input_filter: 'int'
            halign: 'center'
            font_size: sp(20)
            padding: [dp(8), dp(10)]
        Spinner:
            id: ampm_spinner
            text: 'AM'
            values: ['AM', 'PM']
            background_normal: ''
            background_color: 0.9, 0.95, 0.96, 1
            color: 0.07, 0.4, 0.42, 1
            bold: True
            size_hint_x: 1.1
    TealButton:
        text: 'Save timer'
        on_release: root.save()
    BoxLayout:
        size_hint_y: None
        height: dp(46)
        spacing: dp(10)
        SoftButton:
            text: 'Test'
            on_release: root.test()
        SoftButton:
            text: 'Stop'
            on_release: root.stop()
    Txt:
        text: root.status_text
        font_size: sp(13)
        color: 0.07, 0.44, 0.3, 1

<ConnectScreen>:
    name: 'connect'
    BoxLayout:
        orientation: 'vertical'
        padding: dp(24)
        spacing: dp(14)
        Widget:
            size_hint_y: 0.12
        Txt:
            text: 'DailyMed'
            bold: True
            font_size: sp(34)
            halign: 'center'
        Txt:
            text: 'Connect to your device'
            font_size: sp(18)
            halign: 'center'
        Txt:
            text: 'Enter the IP address shown on the device screen. Your phone and the device must be on the same WiFi.'
            font_size: sp(14)
            halign: 'center'
        TextInput:
            id: address_input
            hint_text: 'e.g. 192.168.1.50'
            multiline: False
            size_hint_y: None
            height: dp(48)
            font_size: sp(18)
            padding: [dp(12), dp(12)]
            on_text_validate: root.connect()
        TealButton:
            id: connect_button
            text: 'Connect'
            on_release: root.connect()
        Txt:
            id: message
            color: 0.71, 0.15, 0.2, 1
            halign: 'center'
        Widget:

<ControlScreen>:
    name: 'control'
    BoxLayout:
        orientation: 'vertical'
        BoxLayout:
            size_hint_y: None
            height: dp(56)
            padding: dp(12), dp(6)
            spacing: dp(8)
            canvas.before:
                Color:
                    rgba: 0.03, 0.49, 0.52, 1
                Rectangle:
                    pos: self.pos
                    size: self.size
            Label:
                text: 'DailyMed'
                bold: True
                font_size: sp(20)
                text_size: self.size
                halign: 'left'
                valign: 'middle'
            Label:
                id: connection_label
                text: 'Connecting...'
                font_size: sp(13)
                text_size: self.size
                halign: 'right'
                valign: 'middle'
            SoftButton:
                text: 'Change'
                size_hint_x: None
                width: dp(80)
                height: dp(40)
                pos_hint: {'center_y': 0.5}
                on_release: app.disconnect()
        ScrollView:
            do_scroll_x: False
            BoxLayout:
                orientation: 'vertical'
                size_hint_y: None
                height: self.minimum_height
                padding: dp(12)
                spacing: dp(12)
                Card:
                    Txt:
                        text: 'Device status'
                        bold: True
                        font_size: sp(18)
                    Txt:
                        id: time_label
                        text: 'Device time: --'
                    Txt:
                        id: sos_label
                        text: 'SOS alarm: --'
                    BoxLayout:
                        size_hint_y: None
                        height: dp(46)
                        spacing: dp(10)
                        RedButton:
                            text: 'Trigger SOS'
                            on_release: app.set_sos(True)
                        SoftButton:
                            text: 'Stop SOS'
                            on_release: app.set_sos(False)
                    SoftButton:
                        text: 'Reload timers from device'
                        on_release: app.reload_timers()
                BoxLayout:
                    id: cards
                    orientation: 'vertical'
                    size_hint_y: None
                    height: self.minimum_height
                    spacing: dp(12)
"""


def normalize_address(text):
    text = text.strip().lower()
    for prefix in ("http://", "https://"):
        if text.startswith(prefix):
            text = text[len(prefix):]
    text = text.split("/")[0]
    if not text:
        raise ValueError("Enter the IP address shown on the device screen.")
    allowed = set("abcdefghijklmnopqrstuvwxyz0123456789.-:")
    if any(character not in allowed for character in text):
        raise ValueError("That address has characters that are not allowed.")
    if ":" not in text:
        text += ":%d" % DEFAULT_PORT
    return "http://" + text


def http_get(base_url, path, params=None, timeout=4):
    url = base_url + path
    if params:
        url += "?" + urllib.parse.urlencode(params)
    with urllib.request.urlopen(url, timeout=timeout) as response:
        body = response.read().decode("utf-8")
    return json.loads(body)


def run_async(work, done):
    def target():
        result = None
        error = None
        try:
            result = work()
        except urllib.error.HTTPError as exc:
            error = "The device replied with error %d" % exc.code
        except (urllib.error.URLError, socket.timeout, OSError):
            error = "Cannot reach the device"
        except ValueError:
            error = "Unexpected reply from the device"
        Clock.schedule_once(lambda dt: done(result, error))

    threading.Thread(target=target, daemon=True).start()


class Card(BoxLayout):
    pass


class CompartmentCard(Card):
    index = NumericProperty(0)
    title = StringProperty("")
    state_text = StringProperty("")
    status_text = StringProperty("")

    def load_from(self, config):
        hour24 = int(config.get("hour", 8))
        minute = int(config.get("minute", 0))
        self.ids.enabled_switch.active = bool(config.get("enabled", True))
        self.ids.ampm_spinner.text = "PM" if hour24 >= 12 else "AM"
        self.ids.hour_input.text = str(hour24 % 12 or 12)
        self.ids.minute_input.text = "%02d" % minute

    def read_time(self):
        hour = int(self.ids.hour_input.text)
        minute = int(self.ids.minute_input.text)
        if not 1 <= hour <= 12 or not 0 <= minute <= 59:
            raise ValueError("out of range")
        hour24 = hour % 12 + (12 if self.ids.ampm_spinner.text == "PM" else 0)
        return hour24, minute

    def finish(self, error, ok_text):
        self.status_text = error if error else ok_text

    def save(self):
        try:
            hour24, minute = self.read_time()
        except ValueError:
            self.status_text = "Enter an hour from 1 to 12 and a minute from 0 to 59"
            return

        params = {
            "index": self.index,
            "hour": hour24,
            "minute": minute,
            "enabled": "1" if self.ids.enabled_switch.active else "0",
        }
        self.status_text = "Saving..."
        App.get_running_app().call("/set", params, lambda data, error: self.finish(error, "Saved on the device"))

    def test(self):
        self.status_text = "Starting test..."
        App.get_running_app().call("/activate", {"index": self.index}, lambda data, error: self.finish(error, "Test started"))

    def stop(self):
        self.status_text = "Stopping..."
        App.get_running_app().call("/stop", {"index": self.index}, lambda data, error: self.finish(error, "Stopped"))


class ConnectScreen(Screen):
    def connect(self):
        app = App.get_running_app()

        try:
            base_url = normalize_address(self.ids.address_input.text)
        except ValueError as exc:
            self.ids.message.text = str(exc)
            return

        self.ids.message.text = "Connecting..."
        self.ids.connect_button.disabled = True

        def done(data, error):
            self.ids.connect_button.disabled = False
            if not error and (not isinstance(data, dict) or "compartments" not in data):
                error = "That does not look like a DailyMed device"
            if error:
                self.ids.message.text = error + ". Check the IP address and the WiFi."
                return
            self.ids.message.text = ""
            app.open_device(base_url, data)

        run_async(lambda: http_get(base_url, "/api/config"), done)


class ControlScreen(Screen):
    pass


class DailyMedApp(App):
    def build(self):
        self.title = "DailyMed"
        Builder.load_string(KV)

        self.store = JsonStore(join(self.user_data_dir, "settings.json"))
        self.base_url = ""
        self.clock_base = None
        self.clock_mark = 0.0
        self.fail_count = 0
        self.busy = False
        self.cards = []
        self.poll_event = None
        self.tick_event = None

        self.manager = ScreenManager(transition=SlideTransition())
        self.connect_screen = ConnectScreen()
        self.control_screen = ControlScreen()
        self.manager.add_widget(self.connect_screen)
        self.manager.add_widget(self.control_screen)

        if self.store.exists("device"):
            self.connect_screen.ids.address_input.text = self.store.get("device")["address"]

        Window.bind(on_keyboard=self.on_keyboard)
        return self.manager

    def on_keyboard(self, window, key, *args):
        if key == 27 and self.manager.current == "control":
            self.disconnect()
            return True
        return False

    def call(self, path, params, done):
        base_url = self.base_url
        run_async(lambda: http_get(base_url, path, params), done)

    def device_now(self):
        return self.clock_base + (time.monotonic() - self.clock_mark)

    def open_device(self, base_url, data):
        self.base_url = base_url
        self.store.put("device", address=base_url.replace("http://", ""))
        self.fail_count = 0
        self.busy = False
        self.clock_base = None

        container = self.control_screen.ids.cards
        container.clear_widgets()
        self.cards = []
        for index in range(3):
            card = CompartmentCard(index=index, title=NAMES[index])
            self.cards.append(card)
            container.add_widget(card)

        self.apply_config(data, True)

        self.manager.transition.direction = "left"
        self.manager.current = "control"
        self.stop_timers()
        self.poll_event = Clock.schedule_interval(self.poll, 2)
        self.tick_event = Clock.schedule_interval(self.tick, 0.25)

    def stop_timers(self):
        if self.poll_event:
            self.poll_event.cancel()
            self.poll_event = None
        if self.tick_event:
            self.tick_event.cancel()
            self.tick_event = None

    def disconnect(self):
        self.stop_timers()
        self.manager.transition.direction = "right"
        self.manager.current = "connect"

    def apply_config(self, data, load_inputs):
        ids = self.control_screen.ids
        ids.connection_label.text = "Connected"
        ids.sos_label.text = "SOS alarm: " + ("ACTIVE" if data.get("sosActive") else "OFF")

        epoch = data.get("epoch", 0)
        if epoch and epoch > 0:
            new_base = epoch + 0.5
            if self.clock_base is None or abs(self.device_now() - new_base) > 1.5:
                self.clock_base = new_base
                self.clock_mark = time.monotonic()
        else:
            self.clock_base = None
            ids.time_label.text = "Device time: not available"

        for index, config in enumerate(data.get("compartments", [])[:3]):
            card = self.cards[index]
            card.state_text = "Status: " + str(config.get("state", ""))
            if load_inputs:
                card.load_from(config)

    def tick(self, dt):
        if self.clock_base is None:
            return
        stamp = time.strftime("%Y-%m-%d %I:%M:%S %p", time.gmtime(self.device_now()))
        self.control_screen.ids.time_label.text = "Device time: " + stamp

    def poll(self, dt):
        if self.busy:
            return
        self.busy = True

        def done(data, error):
            self.busy = False
            if error:
                self.fail_count += 1
                if self.fail_count >= 2:
                    self.control_screen.ids.connection_label.text = "Not connected"
                return
            self.fail_count = 0
            self.apply_config(data, False)

        self.call("/api/config", None, done)

    def reload_timers(self):
        def done(data, error):
            if error:
                self.control_screen.ids.connection_label.text = "Not connected"
                return
            self.apply_config(data, True)

        self.call("/api/config", None, done)

    def set_sos(self, active):
        def done(data, error):
            if error:
                self.control_screen.ids.connection_label.text = "Not connected"
                return
            self.control_screen.ids.sos_label.text = "SOS alarm: " + ("ACTIVE" if active else "OFF")

        self.call("/sos", {"active": "1" if active else "0"}, done)


if __name__ == "__main__":
    DailyMedApp().run()
