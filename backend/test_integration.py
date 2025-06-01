import unittest
from unittest.mock import patch, MagicMock

@patch('main.ImageGrab.grab')
@patch('main.pyautogui.moveTo')
@patch('main.pyautogui.click')
@patch('main.socket.socket')
@patch('main.select_monitor_interactively')
class ServerIntegrationTest(unittest.TestCase):
    def test_server_receives_mouse_event(self, mock_select_monitor, mock_socket, mock_click, mock_moveTo, mock_grab):
        mock_monitor = MagicMock()
        mock_monitor.x = 0
        mock_monitor.y = 0
        mock_monitor.width = 100
        mock_monitor.height = 100
        mock_monitor.bbox = (0, 0, 100, 100)
        mock_select_monitor.return_value = mock_monitor

        mock_image = MagicMock()
        mock_image.tobytes.return_value = b'fakebytes'
        mock_grab.return_value = mock_image

        mock_conn = MagicMock()
        mock_socket_instance = MagicMock()
        mock_socket_instance.accept.return_value = (mock_conn, ('127.0.0.1', 54321))
        mock_socket.return_value = mock_socket_instance

        fake_mouse_event = b"MOUSE:left_down,0.5,0.5\n"

        def recv_side_effect(*args, **kwargs):
            if not hasattr(recv_side_effect, 'called'):
                recv_side_effect.called = True
                return fake_mouse_event
            raise Exception("STOP")  # вместо KeyboardInterrupt

        mock_conn.recv.side_effect = recv_side_effect

        import main

        try:
            main.main()
        except Exception as e:
            if str(e) != "STOP":
                raise

        mock_moveTo.assert_called_once()
        mock_click.assert_called_once_with(button='left')
        mock_conn.sendall.assert_called()
        assert mock_conn.sendall.call_args[0][0].startswith(b"IMG:")

if __name__ == '__main__':
    unittest.main()