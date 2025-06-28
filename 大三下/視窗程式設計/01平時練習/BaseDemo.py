from tkinter import *
class BaseDemo:
    def __init__(self, window=None):
        if window is None:
            self.window = Tk()
        else:
            self.window = window
        self.container = None
        
    def set_container(self, container):
        self.container = container
        
    def start(self):
        self.window.mainloop()

class DemoContainer(BaseDemo):
    def __init__(self):
        super().__init__()
        self.window.geometry('')
        self.demos = []
        
    def add_demo(self, demo_class):
        demo = demo_class(self.window)
        self.demos.append(demo)
        return demo
        
    def get_demo(self, demo_class):
        for demo in self.demos:
            if isinstance(demo, demo_class):
                return demo
        return None