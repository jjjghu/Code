from django.utils.deprecation import MiddlewareMixin
import logging
logger = logging.getLogger(__name__)

class SimpleMiddleware(MiddlewareMixin):
    def __init__(self, get_response):
        self.get_response = get_response
        logger.warning('---- One-time configuration and initialization. ----')
    def __call__(self, request):
        logger.warning('YO HA') # 傳出傳入途中要做的事情
        response = self.get_response(request)
        logger.warning('SMILE')
        return response